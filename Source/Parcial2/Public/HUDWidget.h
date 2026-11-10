// Fill out your copyright notice in the Description page of Project Settings.
 
#pragma once
 
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/PEV2_GameState.h" // necesario para el tipo EPEV2Phase
#include "HUDWidget.generated.h"
 
class UButton;
 
UCLASS()
class PARCIAL2_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
    
protected:
    
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
 

	UPROPERTY(meta = (BindWidget))
	UButton* BTN_BackToMenu;
 
	
	UPROPERTY(meta = (BindWidget))
	UButton* BTN_StartMatch;
    
	UFUNCTION()
	void OnBackToMenuClicked();
 
	UFUNCTION()
	void OnStartMatchClicked();
 
	
	UFUNCTION()
	void HandlePhaseChanged(EPEV2Phase NewPhase);
 
private:
	
	bool bBoundToGameState = false;
	void TryBindToGameState();
	void RefreshStartButton(EPEV2Phase Phase);
};
 