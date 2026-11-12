// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "PEV2_GameState.generated.h"
 

UENUM(BlueprintType)
enum class EPEV2Phase : uint8
{
    Lobby   UMETA(DisplayName = "Lobby"),
    Playing UMETA(DisplayName = "Jugando"),
    Ended   UMETA(DisplayName = "Fin")
};
 

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPhaseChanged, EPEV2Phase, NewPhase);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerFell, const FString&, PlayerName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerListChanged);
 
UCLASS()
class PARCIAL2_API APEV2_GameState : public AGameState
{
    GENERATED_BODY()
 
public:
    APEV2_GameState();
 
    
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
 
    
    void SetPhase(EPEV2Phase NewPhase);
 
  
    void SetWinner(APlayerState* NewWinner);
 
   
    void StartRoundClock();
    void StopRoundClock();
 
    UFUNCTION(BlueprintPure, Category = "Match")
    EPEV2Phase GetPhase() const { return Phase; }
 
    UFUNCTION(BlueprintPure, Category = "Match")
    APlayerState* GetWinner() const { return Winner; }
 
   
    UFUNCTION(BlueprintPure, Category = "Match")
    float GetRoundElapsedSeconds() const;
 
    UPROPERTY(BlueprintAssignable, Category = "Match")
    FOnPhaseChanged OnPhaseChanged;
 

    UPROPERTY(BlueprintAssignable, Category = "Match")
    FOnPlayerFell OnPlayerFell;
 
   
    UPROPERTY(BlueprintAssignable, Category = "Match")
    FOnPlayerListChanged OnPlayerListChanged;
 
   
    UFUNCTION(NetMulticast, Unreliable)
    void Multicast_PlayerEliminated(const FString& PlayerName);
 
protected:
    
    UPROPERTY(ReplicatedUsing = OnRep_Phase)
    EPEV2Phase Phase;
 
   
    UPROPERTY(Replicated)
    TObjectPtr<APlayerState> Winner;
 
    
    UPROPERTY(Replicated)
    float RoundStartTime;
 
    UPROPERTY(Replicated)
    float RoundEndTime;
 
    
    UFUNCTION()
    void OnRep_Phase();
};
 