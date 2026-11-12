// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PEV2_GameMode.generated.h"
 
class APEV2_PlayerState;
 
UCLASS()
class PARCIAL2_API APEV2_GameMode : public AGameMode
{
	GENERATED_BODY()
 
public:
	APEV2_GameMode();
 
	virtual void Logout(AController* Exiting) override;
 
	
	void RequestStartMatch(APlayerController* Requester);
 
	
	void HandlePlayerEliminated(APEV2_PlayerState* Victim);
 
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Match")
	FName ArenaSpawnTag;
 
	
	UPROPERTY(EditDefaultsOnly, Category = "Match")
	float ReturnToLobbyDelay;
 
private:
	
	TArray<TWeakObjectPtr<APEV2_PlayerState>> MatchParticipants;
 
	FTimerHandle ReturnToLobbyTimer;
	FTimerHandle LogoutCheckTimer;
 
	void TeleportPawnTo(APawn* Pawn, const AActor* Target);
	void TeleportPlayersToArena();
	void SendPlayerToBalcony(APlayerController* PC);
 
	void CheckWinCondition();
	void FinishRound(APEV2_PlayerState* Winner);
	void ResetToLobby();
};
 