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
 
// Aviso para la UI: "la fase cambió". El HUD se va a suscribir a esto.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseChanged, EPEV2Phase, NewPhase);
 
UCLASS()
class PARCIAL2_API APEV2_GameState : public AGameState
{
	GENERATED_BODY()
 
public:
	APEV2_GameState();
 
	// Obligatoria para cualquier variable replicada (paso 3 de la clase 5)
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
 
	// SOLO el servidor puede cambiar la fase
	void SetPhase(EPEV2Phase NewPhase);
 
	UFUNCTION(BlueprintPure, Category = "Match")
	EPEV2Phase GetPhase() const { return Phase; }
 
	UPROPERTY(BlueprintAssignable, Category = "Match")
	FOnPhaseChanged OnPhaseChanged;
 
protected:
	// Variable replicada con RepNotify (paso 2 de la clase 6)
	UPROPERTY(ReplicatedUsing = OnRep_Phase)
	EPEV2Phase Phase;
 
	// Se ejecuta en los CLIENTES cuando llega un cambio de Phase
	UFUNCTION()
	void OnRep_Phase();
};
 