// Fill out your copyright notice in the Description page of Project Settings.
 
 
#include "HUDWidget.h"
 
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Widget.h"
#include "Engine/World.h"
#include "Framework/PEV2_PlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
 
void UHUDWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    if (BTN_BackToMenu)
    {
       BTN_BackToMenu->OnClicked.AddDynamic(this, &UHUDWidget::OnBackToMenuClicked);
    }
 
    if (BTN_StartMatch)
    {
        BTN_StartMatch->OnClicked.AddDynamic(this, &UHUDWidget::OnStartMatchClicked);
        BTN_StartMatch->SetVisibility(ESlateVisibility::Collapsed); 
    }
 
    if (EndScreen)
    {
        EndScreen->SetVisibility(ESlateVisibility::Collapsed);
    }
 
    if (TXT_FallMessage)
    {
        TXT_FallMessage->SetVisibility(ESlateVisibility::Collapsed);
    }
 
    TryBindToGameState();
}
 
void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
 
    
    if (!bBoundToGameState)
    {
        TryBindToGameState();
        return;
    }
 
   
    UpdateAccumulator += InDeltaTime;
    if (UpdateAccumulator >= 0.1f)
    {
        UpdateAccumulator = 0.0f;
        UpdateTimer();
    }
}
 
void UHUDWidget::TryBindToGameState()
{
    if (bBoundToGameState)
    {
        return;
    }
 
    UWorld* World = GetWorld();
    APEV2_GameState* GS = World ? World->GetGameState<APEV2_GameState>() : nullptr;
    if (!GS)
    {
        return;
    }
 
  
    GS->OnPhaseChanged.AddDynamic(this, &UHUDWidget::HandlePhaseChanged);
    GS->OnPlayerFell.AddDynamic(this, &UHUDWidget::HandlePlayerFell);
    bBoundToGameState = true;
 
  
    RefreshForPhase(GS->GetPhase());
    UpdateTimer();
}
 
void UHUDWidget::HandlePhaseChanged(EPEV2Phase NewPhase)
{
    RefreshForPhase(NewPhase);
}
 
void UHUDWidget::HandlePlayerFell(const FString& PlayerName)
{
    if (!TXT_FallMessage)
    {
        return;
    }
 
    TXT_FallMessage->SetText(FText::FromString(FString::Printf(TEXT("%s ha caido"), *PlayerName)));
    TXT_FallMessage->SetVisibility(ESlateVisibility::HitTestInvisible);
 
    
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().SetTimer(FallMessageTimer, this, &UHUDWidget::HideFallMessage, 3.0f, false);
    }
}
 
void UHUDWidget::HideFallMessage()
{
    if (TXT_FallMessage)
    {
        TXT_FallMessage->SetVisibility(ESlateVisibility::Collapsed);
    }
}
 
void UHUDWidget::RefreshForPhase(EPEV2Phase Phase)
{
    APlayerController* PC = GetOwningPlayer();
 
  
    const bool bIsHost = PC && PC->HasAuthority();
    const bool bShowStart = bIsHost && Phase == EPEV2Phase::Lobby;
 
    if (BTN_StartMatch)
    {
        BTN_StartMatch->SetVisibility(bShowStart ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
 
   
    if (bIsHost && PC)
    {
        if (bShowStart)
        {
            PC->SetShowMouseCursor(true);
            PC->SetInputMode(FInputModeGameAndUI());
        }
        else
        {
            PC->SetShowMouseCursor(false);
            PC->SetInputMode(FInputModeGameOnly());
        }
    }
 
    
    switch (Phase)
    {
    case EPEV2Phase::Lobby:
        ShowStatusMessage(bIsHost
            ? FText::FromString(TEXT("Tocá EMPEZAR cuando estén todos los jugadores"))
            : FText::FromString(TEXT("Esperando que el host empiece la partida...")));
        break;
    case EPEV2Phase::Playing:
        ShowStatusMessage(FText::FromString(TEXT("¡Esquivá los láseres!")));
        break;
    default:
        ShowStatusMessage(FText::GetEmpty());
        break;
    }
 
    RefreshEndScreen(Phase);
}
 
void UHUDWidget::RefreshEndScreen(EPEV2Phase Phase)
{
    if (!EndScreen)
    {
        return;
    }
 
   
    if (Phase != EPEV2Phase::Ended)
    {
        EndScreen->SetVisibility(ESlateVisibility::Collapsed);
        return;
    }
 
    const UWorld* World = GetWorld();
    const APEV2_GameState* GS = World ? World->GetGameState<APEV2_GameState>() : nullptr;
    const APlayerState* Winner = GS ? GS->GetWinner() : nullptr;
 
    if (TXT_WinnerName)
    {
        TXT_WinnerName->SetText(Winner
            ? FText::FromString(Winner->GetPlayerName())
            : FText::FromString(TEXT("Nadie")));
    }
 
   
    EndScreen->SetVisibility(ESlateVisibility::HitTestInvisible);
}
 
void UHUDWidget::UpdateTimer()
{
    if (!TXT_Timer)
    {
        return;
    }
 
    const UWorld* World = GetWorld();
    const APEV2_GameState* GS = World ? World->GetGameState<APEV2_GameState>() : nullptr;
    if (!GS)
    {
        return;
    }
 
    const int32 TotalSeconds = FMath::FloorToInt(GS->GetRoundElapsedSeconds());
    TXT_Timer->SetText(FText::FromString(
        FString::Printf(TEXT("%02d:%02d"), TotalSeconds / 60, TotalSeconds % 60)));
}
 
void UHUDWidget::ShowStatusMessage(const FText& Message)
{
    if (TXT_Status)
    {
        TXT_Status->SetText(Message);
    }
}
 
void UHUDWidget::OnStartMatchClicked()
{
    if (APEV2_PlayerController* PC = Cast<APEV2_PlayerController>(GetOwningPlayer()))
    {
        PC->RequestStartMatch();
    }
}
 
void UHUDWidget::OnBackToMenuClicked()
{
   
    UGameplayStatics::OpenLevel(this, FName("Lvl_Menu"));
}
 