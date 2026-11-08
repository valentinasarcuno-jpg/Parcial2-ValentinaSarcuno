// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UButton;


/**
 * 
 */
UCLASS()
class PARCIAL2_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	
	virtual void NativeConstruct() override;

	// (Botones)
	UPROPERTY(meta = (BindWidget))
	UButton* BTN_BackToMenu;
	
	UFUNCTION()
	void OnBackToMenuClicked();
	
};
