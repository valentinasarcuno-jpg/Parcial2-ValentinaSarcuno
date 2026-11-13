// Fill out your copyright notice in the Description page of Project Settings.

#include "Framework/PEV2_PlayerController.h"
 
#include "Blueprint/UserWidget.h"
#include "Core/PEV2_GameInstance.h"
#include "Engine/Engine.h"
#include "Framework/PEV2_GameMode.h"
#include "HUDWidget.h"
 
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
 
    
    if (IsLocalController())
    {
        if (const UPEV2_GameInstance* GI = Cast<UPEV2_GameInstance>(GetGameInstance()))
        {
            const FString& ChosenName = GI->GetDesiredPlayerName();
            if (!ChosenName.IsEmpty())
            {
                Server_SetPlayerName(ChosenName);
            }
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
   
    if (UHUDWidget* HUD = Cast<UHUDWidget>(HUDWidget))
    {
        HUD->ShowStatusMessage(FText::FromString(TEXT("Caíste. Mirá la partida desde el Balcón.")));
    }
    else if (GEngine)
    {
       
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("¡QUEDASTE ELIMINADO!"));
    }
}
 
void APEV2_PlayerController::Server_SetPlayerName_Implementation(const FString& NewName)
{
   
    FString Clean;
    for (const TCHAR Char : NewName.TrimStartAndEnd())
    {
     
        if (FChar::IsAlnum(Char) || Char == TEXT(' ') || Char == TEXT('-') || Char == TEXT('_'))
        {
            Clean.AppendChar(Char);
        }
    }
    Clean = Clean.Left(15);
 
    if (Clean.IsEmpty())
    {
        return;
    }
 
   
    if (APlayerState* PS = GetPlayerState<APlayerState>())
    {
        PS->SetPlayerName(Clean);
    }
}
 