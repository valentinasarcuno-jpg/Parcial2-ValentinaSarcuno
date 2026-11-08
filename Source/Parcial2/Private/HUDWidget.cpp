// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (BTN_BackToMenu)
	{
		BTN_BackToMenu->OnClicked.AddDynamic(this, &UHUDWidget::OnBackToMenuClicked);
	}
}

void UHUDWidget::OnBackToMenuClicked()
{
	
	UGameplayStatics::OpenLevel(this, FName("Lvl_Menu"));
}
