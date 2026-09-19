// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUIWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// (Añadimos la funcion al boton)
	if (BTN_Play)
	{
		BTN_Play->OnClicked.AddDynamic(this, &UMainMenuUIWidget::OnPlayClicked);
	}

	if (BTN_Quit)
	{
		BTN_Quit->OnClicked.AddDynamic(this, &UMainMenuUIWidget::OnQuitClicked);
	}
}

void UMainMenuUIWidget::OnPlayClicked()
{
	// (La funcion esta abre el nivel)) 
	UGameplayStatics::OpenLevel(this, FName("Lvl_ThirdPerson"));
}

void UMainMenuUIWidget::OnHostClicked()
{
}

void UMainMenuUIWidget::OnQuitClicked()
{
	// (Cerrar juego)
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
}

