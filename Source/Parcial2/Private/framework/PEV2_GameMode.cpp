// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PEV2_GameMode.h"
 
#include "Framework/PEV2_GameState.h"
#include "Framework/PEV2_PlayerState.h"
#include "TimerManager.h"
 
APEV2_GameMode::APEV2_GameMode()
{
	
	GameStateClass = APEV2_GameState::StaticClass();
	PlayerStateClass = APEV2_PlayerState::StaticClass();
 
	
	bDelayedStart = false;
}
 
void APEV2_GameMode::BeginPlay()
{
	Super::BeginPlay();
 
	
	GetWorldTimerManager().SetTimer(TestTimer, this, &APEV2_GameMode::TestChangePhase, 2.0f, false);
}
 
void APEV2_GameMode::TestChangePhase()
{
	
	if (APEV2_GameState* GS = GetGameState<APEV2_GameState>())
	{
		GS->SetPhase(EPEV2Phase::Playing);
	}
}
 