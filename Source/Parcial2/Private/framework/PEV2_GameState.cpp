// Fill out your copyright notice in the Description page of Project Settings.


#include "framework/PEV2_GameState.h"


#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"
 
APEV2_GameState::APEV2_GameState()
{
	
	Phase = EPEV2Phase::Lobby;
}
 
void APEV2_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
 
	
	DOREPLIFETIME(APEV2_GameState, Phase);
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

void APEV2_GameState::Multicast_PlayerEliminated(const FString& String)
{
}

void APEV2_GameState::SetWinner(std::nullptr_t Null)
{
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
	}
}
 