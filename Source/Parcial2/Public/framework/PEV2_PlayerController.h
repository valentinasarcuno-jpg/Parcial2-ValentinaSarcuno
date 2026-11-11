// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PEV2_PlayerController.generated.h"
 
class UUserWidget;
 
UCLASS()
class PARCIAL2_API APEV2_PlayerController : public APlayerController
{
	GENERATED_BODY()
 
public:
	virtual void BeginPlay() override;
 
	
	UFUNCTION(BlueprintCallable, Category = "Match")
	void RequestStartMatch();
 
	
	UFUNCTION(Client, Reliable)
	void Client_NotifyEliminated();
 
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> HUDWidgetClass;
 
	UPROPERTY()
	TObjectPtr<UUserWidget> HUDWidget;
 
	
	UFUNCTION(Server, Reliable)
	void Server_RequestStartMatch();
};
 