// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PEV2_PlayerState.h"
 
#include "Framework/PEV2_GameState.h"
#include "Net/UnrealNetwork.h"
 
APEV2_PlayerState::APEV2_PlayerState()
{
	bIsDead = false;
	SurvivalTime = 0.0f;
}
 
void APEV2_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
 
	
	DOREPLIFETIME(APEV2_PlayerState, bIsDead);
	DOREPLIFETIME(APEV2_PlayerState, SurvivalTime);
}
 
void APEV2_PlayerState::SetDead(bool bNewDead)
{
	
	if (!HasAuthority() || bIsDead == bNewDead)
	{
		return;
	}
 
	bIsDead = bNewDead;
 
	
	OnRep_IsDead();
}
 
void APEV2_PlayerState::SetSurvivalTime(float NewTime)
{
	if (!HasAuthority())
	{
		return;
	}
 
	SurvivalTime = NewTime;
}
 
void APEV2_PlayerState::OnRep_IsDead()
{
	
	NotifyListChanged();
}
 
void APEV2_PlayerState::NotifyListChanged()
{
	if (UWorld* World = GetWorld())
	{
		if (APEV2_GameState* GS = World->GetGameState<APEV2_GameState>())
		{
			GS->OnPlayerListChanged.Broadcast();
		}
	}
}
 