// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PEV2_GameState.h"
 
#include "Net/UnrealNetwork.h"
 
APEV2_GameState::APEV2_GameState()
{
   
    Phase = EPEV2Phase::Lobby;
    Winner = nullptr;
    RoundStartTime = 0.0f;
    RoundEndTime = 0.0f;
}
 
void APEV2_GameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
   
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
 
    DOREPLIFETIME(APEV2_GameState, Phase);
    DOREPLIFETIME(APEV2_GameState, Winner);
    DOREPLIFETIME(APEV2_GameState, RoundStartTime);
    DOREPLIFETIME(APEV2_GameState, RoundEndTime);
}
 
void APEV2_GameState::SetPhase(EPEV2Phase NewPhase)
{
    
    if (!HasAuthority())
    {
        return;
    }
 
    if (Phase == NewPhase)
    {
        return;
    }
 
    Phase = NewPhase;
 
    
    OnRep_Phase();
}
 
void APEV2_GameState::SetWinner(APlayerState* NewWinner)
{
    if (!HasAuthority())
    {
        return;
    }
 
    Winner = NewWinner;
}
 
void APEV2_GameState::StartRoundClock()
{
    if (!HasAuthority())
    {
        return;
    }
 
    
    RoundStartTime = GetServerWorldTimeSeconds();
    RoundEndTime = 0.0f;
}
 
void APEV2_GameState::StopRoundClock()
{
    if (!HasAuthority())
    {
        return;
    }
 
    RoundEndTime = GetServerWorldTimeSeconds();
}
 
float APEV2_GameState::GetRoundElapsedSeconds() const
{
    if (Phase == EPEV2Phase::Lobby)
    {
        return 0.0f;
    }
 
    const bool bFrozen = (Phase == EPEV2Phase::Ended && RoundEndTime > 0.0f);
    const float End = bFrozen ? RoundEndTime : GetServerWorldTimeSeconds();
 
    return FMath::Max(0.0f, End - RoundStartTime);
}
 
void APEV2_GameState::OnRep_Phase()
{
  
    OnPhaseChanged.Broadcast(Phase);
}
 
void APEV2_GameState::Multicast_PlayerEliminated_Implementation(const FString& PlayerName)
{
   
    OnPlayerFell.Broadcast(PlayerName);
}
 