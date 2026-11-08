// Fill out your copyright notice in the Description page of Project Settings.


#include "framework/PEV2_GameMode.h"

#include "Framework/PEV2_GameState.h"
#include "TimerManager.h"
 
APEV2_GameMode::APEV2_GameMode()
{
	// Le decimos al GameMode qué GameState usar.
	// (AGameMode exige un AGameState, no un AGameStateBase: clase 8)
	GameStateClass = APEV2_GameState::StaticClass();
 
	// No usamos el "inicio demorado" de Unreal: los jugadores tienen que
	// aparecer ya mismo (en el Balcón). La fase la manejamos nosotros.
	bDelayedStart = false;
}
 
void APEV2_GameMode::BeginPlay()
{
	Super::BeginPlay();
 
	// ---- PRUEBA TEMPORAL: a los 5 segundos pasamos de Lobby a Jugando ----
	GetWorldTimerManager().SetTimer(TestTimer, this, &APEV2_GameMode::TestChangePhase, 5.0f, false);
}
 
void APEV2_GameMode::TestChangePhase()
{
	// GetGameState<T>() nos da nuestro GameState ya casteado (solo existe en el servidor el GameMode)
	if (APEV2_GameState* GS = GetGameState<APEV2_GameState>())
	{
		GS->SetPhase(EPEV2Phase::Playing);
	}
}
 