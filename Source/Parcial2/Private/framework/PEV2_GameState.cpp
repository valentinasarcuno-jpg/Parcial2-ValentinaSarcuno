// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PEV2_GameState.h"
 
#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"
 
APEV2_GameState::APEV2_GameState()
{
    
    Phase = EPEV2Phase::Lobby;
    Winner = nullptr;
}
 
void APEV2_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
 
    DOREPLIFETIME(APEV2_GameState, Phase);
    DOREPLIFETIME(APEV2_GameState, Winner);
}
 
void APEV2_GameState::SetPhase(EPEV2Phase NewPhase)
{
   
    if (!HasAuthority())
    {
        return;
    }
 
    if (Phase == NewPhase)
    {
        return;
    }
 
    Phase = NewPhase;
 
    
    OnRep_Phase();
}
 
void APEV2_GameState::SetWinner(APlayerState* NewWinner)
{
    if (!HasAuthority())
    {
        return;
    }
 
    Winner = NewWinner;
}
 
void APEV2_GameState::OnRep_Phase()
{
   
    OnPhaseChanged.Broadcast(Phase);
 
    
    if (GEngine)
    {
        const TCHAR* Quien = HasAuthority() ? TEXT("SERVIDOR") : TEXT("CLIENTE");
        GEngine->AddOnScreenDebugMessage(
            -1, 4.0f, FColor::Yellow,
            FString::Printf(TEXT("[%s] Fase de la partida: %s"), Quien, *UEnum::GetValueAsString(Phase)));
 
        if (Phase == EPEV2Phase::Ended)
        {
            const FString WinnerName = Winner ? Winner->GetPlayerName() : FString(TEXT("nadie (empate)"));
            GEngine->AddOnScreenDebugMessage(
                -1, 6.0f, FColor::Green,
                FString::Printf(TEXT("[%s] GANADOR: %s"), Quien, *WinnerName));
        }
    }
}
 
void APEV2_GameState::Multicast_PlayerEliminated_Implementation(const FString& PlayerName)
{
    
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(
            -1, 4.0f, FColor::Orange,
            FString::Printf(TEXT("%s fue eliminado"), *PlayerName));
    }
}
 