// Fill out your copyright notice in the Description page of Project Settings.
 
 
#include "MainMenuUIWidget.h"
#include "Components/Button.h"
#include "Core/PEV2_GameInstance.h"
#include "Engine/Engine.h"
#include "Components/EditableText.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
 
void UMainMenuUIWidget::NativeConstruct()
{
    Super::NativeConstruct();
 
    
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
 
   
    SaveChosenName();
 
   
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
 
    
    SaveChosenName();
 
   
    UGameplayStatics::OpenLevel(this, FName(*IP));
}
 
FString UMainMenuUIWidget::GetChosenPlayerName() const
{
    FString Name = TXT_PlayerTAG ? TXT_PlayerTAG->GetText().ToString().TrimStartAndEnd() : FString();
 
    
    Name = Name.Left(15);
 
    
    if (Name.IsEmpty())
    {
        Name = TEXT("Jugador");
    }
 
    return Name;
}
 
void UMainMenuUIWidget::SaveChosenName() const
{
    
    if (UPEV2_GameInstance* GI = Cast<UPEV2_GameInstance>(GetGameInstance()))
    {
        GI->SetDesiredPlayerName(GetChosenPlayerName());
    }
    else if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 8.0f, FColor::Red,
            TEXT("Falta configurar PEV2_GameInstance en Project Settings > Maps & Modes > Game Instance Class"));
    }
}
 
void UMainMenuUIWidget::OnSettingsClicked()
{
}
 
void UMainMenuUIWidget::OnQuitClicked()
{
    
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
}
 