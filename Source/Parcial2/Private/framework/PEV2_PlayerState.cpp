// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PEV2_PlayerState.h"
 
#include "Engine/Engine.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"
 
APEV2_PlayerState::APEV2_PlayerState()
{
	bIsDead = false;
}
 
void APEV2_PlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
 
	
	DOREPLIFETIME(APEV2_PlayerState, bIsDead);
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
 
void APEV2_PlayerState::OnRep_IsDead()
{
	UpdatePawnForDeathState();
 
	
	if (GEngine)
	{
		const TCHAR* Quien = HasAuthority() ? TEXT("SERVIDOR") : TEXT("CLIENTE");
		GEngine->AddOnScreenDebugMessage(
			-1, 4.0f, FColor::Red,
			FString::Printf(TEXT("[%s] %s: eliminado = %s"), Quien, *GetPlayerName(),
							bIsDead ? TEXT("SI") : TEXT("NO")));
	}
}
 
void APEV2_PlayerState::UpdatePawnForDeathState()
{
	
	ACharacter* Character = Cast<ACharacter>(GetPawn());
	if (!Character)
	{
		return;
	}
 
	Character->SetActorHiddenInGame(bIsDead);
	Character->SetActorEnableCollision(!bIsDead);
 
	if (UCharacterMovementComponent* Movement = Character->GetCharacterMovement())
	{
		if (bIsDead)
		{
			Movement->DisableMovement();
		}
		else
		{
			Movement->SetMovementMode(MOVE_Walking);
		}
	}
}
 