// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PEV2_GameState.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPEV2Phase : uint8
{
	Lobby   UMETA(DisplayName = "Lobby"),
	Playing UMETA(DisplayName = "Jugando"),
	Ended   UMETA(DisplayName = "Fin")
};
 

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseChanged, EPEV2Phase, NewPhase);
 
UCLASS()
class PARCIAL2_API APEV2_GameState : public AGameState
{
	GENERATED_BODY()
 
public:
	APEV2_GameState();
 
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
 
	
	void SetPhase(EPEV2Phase NewPhase);
 
	UFUNCTION(BlueprintPure, Category = "Match")
	EPEV2Phase GetPhase() const { return Phase; }
 
	UPROPERTY(BlueprintAssignable, Category = "Match")
	FOnPhaseChanged OnPhaseChanged;
 
protected:
	
	UPROPERTY(ReplicatedUsing = OnRep_Phase)
	EPEV2Phase Phase;
 
	
	UFUNCTION()
	void OnRep_Phase();
};
 