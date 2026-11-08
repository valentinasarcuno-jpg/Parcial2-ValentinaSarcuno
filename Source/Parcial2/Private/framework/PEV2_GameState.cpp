// Fill out your copyright notice in the Description page of Project Settings.


#include "framework/PEV2_GameState.h"


#include "Engine/Engine.h"
#include "Net/UnrealNetwork.h"
 
APEV2_GameState::APEV2_GameState()
{
	// Toda partida empieza en el Lobby (el Balcón)
	Phase = EPEV2Phase::Lobby;
}
 
void APEV2_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	// Siempre llamar al padre: si no, se rompe la replicación de la clase base
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
 
	// Registramos la variable para que el servidor se la mande a los clientes
	DOREPLIFETIME(APEV2_GameState, Phase);
}
 
void APEV2_GameState::SetPhase(EPEV2Phase NewPhase)
{
	// Regla de oro: solo el servidor decide
	if (!HasAuthority())
	{
		return;
	}
 
	if (Phase == NewPhase)
	{
		return;
	}
 
	Phase = NewPhase;
 
	// El host es servidor y cliente a la vez: a él NO se le replica la variable,
	// así que su OnRep no se llama solo. Lo llamamos a mano (clase 6).
	OnRep_Phase();
}
 
void APEV2_GameState::OnRep_Phase()
{
	// Avisamos a quien esté escuchando (más adelante, el HUD)
	OnPhaseChanged.Broadcast(Phase);
 
	// Mensaje de prueba para ver que funciona en cada ventana (se puede borrar después)
	if (GEngine)
	{
		const TCHAR* Quien = HasAuthority() ? TEXT("SERVIDOR") : TEXT("CLIENTE");
		GEngine->AddOnScreenDebugMessage(
			-1, 4.0f, FColor::Yellow,
			FString::Printf(TEXT("[%s] Fase de la partida: %s"), Quien, *UEnum::GetValueAsString(Phase)));
	}
}
 