// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUIWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// (Añadimos la funcion al boton)
	if (BTN_Join)
	{
		BTN_Join->OnClicked.AddDynamic(this, &UMainMenuUIWidget::OnJoinClicked);
	}
	
	if (BTN_Host)
	{
		BTN_Host->OnClicked.AddDynamic(this, &UMainMenuUIWidget::OnHostClicked);
	}

	if (BTN_Quit)
	{
		BTN_Quit->OnClicked.AddDynamic(this, &UMainMenuUIWidget::OnQuitClicked);
	}
}



void UMainMenuUIWidget::OnHostClicked()
{
	
	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->SetShowMouseCursor(false);
	}
 
	
	UGameplayStatics::OpenLevelBySoftObjectPtr(this, Lvl_ThirdPerson, true, TEXT("listen"));
}

void UMainMenuUIWidget::OnJoinClicked()
{
	if (!TXT_IP)
	{
		return;
	}
 
	
	const FString IP = TXT_IP->GetText().ToString().TrimStartAndEnd();
 
	if (IP.IsEmpty())
	{
		UE_LOG(LogTemp, Warning, TEXT("Falta escribir la IP del host para unirse."));
		return;
	}
 
	if (APlayerController* PC = GetOwningPlayer())
	{
		PC->SetInputMode(FInputModeGameOnly());
		PC->SetShowMouseCursor(false);
	}
 
	
	UGameplayStatics::OpenLevel(this, FName(*IP));
}

void UMainMenuUIWidget::OnSettingsClicked()
{
}
 
void UMainMenuUIWidget::OnQuitClicked()
{
	// (Cerrar juego)
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
}

