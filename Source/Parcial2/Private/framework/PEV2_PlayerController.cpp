// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PEV2_PlayerController.h"
 
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "Framework/PEV2_GameMode.h"
 
void APEV2_PlayerController::BeginPlay()
{
	
	Super::BeginPlay();
 

	if (IsLocalController() && HUDWidgetClass)
	{
		HUDWidget = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
		}
	}
}
 
void APEV2_PlayerController::RequestStartMatch()
{
	
	Server_RequestStartMatch();
}
 
void APEV2_PlayerController::Server_RequestStartMatch_Implementation()
{
	
	if (APEV2_GameMode* GM = GetWorld()->GetAuthGameMode<APEV2_GameMode>())
	{
		GM->RequestStartMatch(this);
	}
}
 
void APEV2_PlayerController::Client_NotifyEliminated_Implementation()
{

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("¡QUEDASTE ELIMINADO!"));
	}
}
 

