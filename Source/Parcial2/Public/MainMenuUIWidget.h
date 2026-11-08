// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUIWidget.generated.h"

class UButton;
class UEditableText;

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
	UButton* BTN_Join;
    
	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Host;
 
	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Quit;
    
	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Settings;
 
	UPROPERTY(meta = (BindWidget))
	UEditableText* TXT_IP;

	UPROPERTY(meta = (BindWidget))
	UEditableText* TXT_PlayerTAG;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> Lvl_ThirdPerson;

	// (Funciones de botones)
	UFUNCTION()
	void OnJoinClicked();
    
	UFUNCTION()
	void OnHostClicked();
 
	UFUNCTION()
	void OnQuitClicked();
    
	UFUNCTION()
	void OnSettingsClicked();
};
	

