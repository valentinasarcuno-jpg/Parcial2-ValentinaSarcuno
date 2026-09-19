// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUIWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class PARCIAL2_API UMainMenuUIWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
protected:
	
	virtual void NativeConstruct() override;

	// (Botones)
	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Play;
	
	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Host;

	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Quit;

	// (Funciones de botones)
	UFUNCTION()
	void OnPlayClicked();
	
	UFUNCTION()
	void OnHostClicked();

	UFUNCTION()
	void OnQuitClicked();
};	
	

