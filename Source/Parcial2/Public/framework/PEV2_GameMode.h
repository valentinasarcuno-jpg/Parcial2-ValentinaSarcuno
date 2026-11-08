// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PEV2_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class PARCIAL2_API APEV2_GameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	APEV2_GameMode();
 
protected:
	virtual void BeginPlay() override;
 
private:
	// ---- PRUEBA TEMPORAL (la borramos cuando agreguemos el botón "Empezar") ----
	FTimerHandle TestTimer;
	void TestChangePhase();
};
 
