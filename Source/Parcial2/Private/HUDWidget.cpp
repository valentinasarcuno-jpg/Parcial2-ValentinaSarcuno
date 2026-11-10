// Fill out your copyright notice in the Description page of Project Settings.
 
 
#include "HUDWidget.h"
 
#include "Components/Button.h"
#include "Framework/PEV2_PlayerController.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
 
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
 
    TryBindToGameState();
}
 
void UHUDWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
 
    
    if (!bBoundToGameState)
    {
        TryBindToGameState();
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
    bBoundToGameState = true;
 
   
    RefreshStartButton(GS->GetPhase());
}
 
void UHUDWidget::HandlePhaseChanged(EPEV2Phase NewPhase)
{
    RefreshStartButton(NewPhase);
}
 
void UHUDWidget::RefreshStartButton(EPEV2Phase Phase)
{
    APlayerController* PC = GetOwningPlayer();
 
  
    const bool bIsHost = PC && PC->HasAuthority();
    const bool bShow = bIsHost && Phase == EPEV2Phase::Lobby;
 
    if (BTN_StartMatch)
    {
        BTN_StartMatch->SetVisibility(bShow ? ESlateVisibility::Visible : ESlateVisibility::Collapsed);
    }
 
  
    if (bIsHost && PC)
    {
        if (bShow)
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
 