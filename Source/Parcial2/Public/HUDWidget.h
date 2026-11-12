// Fill out your copyright notice in the Description page of Project Settings.
 
#pragma once
 
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/PEV2_GameState.h" 
#include "HUDWidget.generated.h"
 
class UButton;
class UTextBlock;
class UWidget;
 
UCLASS()
class PARCIAL2_API UHUDWidget : public UUserWidget
{
    GENERATED_BODY()
 
public:
    
    void ShowStatusMessage(const FText& Message);
 
protected:
    virtual void NativeConstruct() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
 
  
    UPROPERTY(meta = (BindWidget))
    UButton* BTN_BackToMenu;
 
   
    UPROPERTY(meta = (BindWidget))
    UButton* BTN_StartMatch;
 
    
    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* TXT_Timer;       
 
    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* TXT_Status;      
 
    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* TXT_FallMessage; 
 
  
    UPROPERTY(meta = (BindWidgetOptional))
    UWidget* EndScreen;
 
    UPROPERTY(meta = (BindWidgetOptional))
    UTextBlock* TXT_WinnerName;
 
    UFUNCTION()
    void OnBackToMenuClicked();
 
    UFUNCTION()
    void OnStartMatchClicked();
 
   
    UFUNCTION()
    void HandlePhaseChanged(EPEV2Phase NewPhase);
 
   
    UFUNCTION()
    void HandlePlayerFell(const FString& PlayerName);
 
private:
    
    bool bBoundToGameState = false;
    float UpdateAccumulator = 0.0f;
    FTimerHandle FallMessageTimer;
 
    void TryBindToGameState();
    void RefreshForPhase(EPEV2Phase Phase);
    void RefreshEndScreen(EPEV2Phase Phase);
    void UpdateTimer();
    void HideFallMessage();
};
 