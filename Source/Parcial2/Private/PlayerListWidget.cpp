// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerListWidget.h"
 
#include "Components/VerticalBox.h"
#include "Framework/PEV2_GameState.h"
#include "PlayerRowWidget.h"
 
void UPlayerListWidget::NativeConstruct()
{
    Super::NativeConstruct();
 
    TryBindToGameState();
    RefreshList();
}
 
void UPlayerListWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);
 
   
    if (!bBoundToGameState)
    {
        TryBindToGameState();
    }
 
 
    UpdateAccumulator += InDeltaTime;
    if (UpdateAccumulator >= 0.1f)
    {
        UpdateAccumulator = 0.0f;
        RefreshList();
    }
}
 
void UPlayerListWidget::TryBindToGameState()
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
 
   
    GS->OnPlayerListChanged.AddDynamic(this, &UPlayerListWidget::HandleListChanged);
    bBoundToGameState = true;
}
 
void UPlayerListWidget::HandleListChanged()
{
    RefreshList();
}
 
void UPlayerListWidget::RefreshList()
{
    const UWorld* World = GetWorld();
    const APEV2_GameState* GS = World ? World->GetGameState<APEV2_GameState>() : nullptr;
    if (!GS || !PlayerListBox || !RowClass)
    {
        return;
    }
 
  
    for (auto It = Rows.CreateIterator(); It; ++It)
    {
        const APEV2_PlayerState* Key = It.Key().Get();
 
        bool bStillConnected = false;
        for (const APlayerState* Player : GS->PlayerArray)
        {
            if (Player == Key)
            {
                bStillConnected = true;
                break;
            }
        }
 
        if (!bStillConnected)
        {
            if (UPlayerRowWidget* OldRow = It.Value().Get())
            {
                OldRow->RemoveFromParent();
            }
            It.RemoveCurrent();
        }
    }
 
 
    for (APlayerState* Player : GS->PlayerArray)
    {
        APEV2_PlayerState* PS = Cast<APEV2_PlayerState>(Player);
        if (!PS)
        {
            continue;
        }
 
        UPlayerRowWidget* Row = nullptr;
        if (TWeakObjectPtr<UPlayerRowWidget>* Existing = Rows.Find(PS))
        {
            Row = Existing->Get();
        }
 
        if (!Row)
        {
            Row = CreateWidget<UPlayerRowWidget>(GetOwningPlayer(), RowClass);
            if (!Row)
            {
                continue;
            }
            PlayerListBox->AddChild(Row);
            Rows.Add(PS, Row);
        }
 
       
        float TimeToShow = -1.0f;
        if (PS->IsDead())
        {
            TimeToShow = PS->GetSurvivalTime();
        }
        else if (GS->GetPhase() == EPEV2Phase::Playing)
        {
            TimeToShow = GS->GetRoundElapsedSeconds();
        }
        else if (PS->GetSurvivalTime() > 0.0f)
        {
            TimeToShow = PS->GetSurvivalTime();
        }
 
        Row->SetData(PS->GetPlayerName(), PS->IsDead(), TimeToShow);
    }
}
 
