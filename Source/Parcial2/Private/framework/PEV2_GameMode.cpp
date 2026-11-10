// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/PEV2_GameMode.h"
 
#include "Engine/Engine.h"
#include "Framework/PEV2_GameState.h"
#include "Framework/PEV2_PlayerController.h"
#include "Framework/PEV2_PlayerState.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
 
APEV2_GameMode::APEV2_GameMode()
{
    
    GameStateClass = APEV2_GameState::StaticClass();
    PlayerStateClass = APEV2_PlayerState::StaticClass();
 
  
    bDelayedStart = false;
 
    ArenaSpawnTag = FName(TEXT("ArenaSpawn"));
    ReturnToLobbyDelay = 8.0f;
}
 
void APEV2_GameMode::Logout(AController* Exiting)
{
    Super::Logout(Exiting);
 
   
    const APEV2_GameState* GS = GetGameState<APEV2_GameState>();
    if (GS && GS->GetPhase() == EPEV2Phase::Playing)
    {
        GetWorldTimerManager().SetTimer(LogoutCheckTimer, this, &APEV2_GameMode::CheckWinCondition, 0.5f, false);
    }
}
 
void APEV2_GameMode::RequestStartMatch(APlayerController* Requester)
{
 
    APEV2_GameState* GS = GetGameState<APEV2_GameState>();
    if (!GS || GS->GetPhase() != EPEV2Phase::Lobby)
    {
        return;
    }
 
    
    if (!Requester || !Requester->IsLocalController())
    {
        return;
    }
 
    
    MatchParticipants.Empty();
    for (APlayerState* Player : GS->PlayerArray)
    {
        if (APEV2_PlayerState* PS = Cast<APEV2_PlayerState>(Player))
        {
            PS->SetDead(false);
            MatchParticipants.Add(PS);
        }
    }
    GS->SetWinner(nullptr);
 
    
    TeleportPlayersToArena();
    GS->SetPhase(EPEV2Phase::Playing);
}
 
void APEV2_GameMode::HandlePlayerEliminated(APEV2_PlayerState* Victim)
{
   
    APEV2_GameState* GS = GetGameState<APEV2_GameState>();
    if (!GS || GS->GetPhase() != EPEV2Phase::Playing)
    {
        return;
    }
 
    if (!Victim || Victim->IsDead())
    {
        return;
    }
 
   
    const bool bIsParticipant = MatchParticipants.ContainsByPredicate(
        [Victim](const TWeakObjectPtr<APEV2_PlayerState>& P) { return P.Get() == Victim; });
    if (!bIsParticipant)
    {
        return;
    }
 
   
    Victim->SetDead(true);
 
   
    if (APEV2_PlayerController* PC = Cast<APEV2_PlayerController>(Victim->GetPlayerController()))
    {
        PC->Client_NotifyEliminated();
    }
 
  
    GS->Multicast_PlayerEliminated(Victim->GetPlayerName());
 
   
    CheckWinCondition();
}
 
void APEV2_GameMode::CheckWinCondition()
{
    APEV2_GameState* GS = GetGameState<APEV2_GameState>();
    if (!GS || GS->GetPhase() != EPEV2Phase::Playing)
    {
        return;
    }
 
    int32 Alive = 0;
    APEV2_PlayerState* LastAlive = nullptr;
 
    for (const TWeakObjectPtr<APEV2_PlayerState>& Weak : MatchParticipants)
    {
        APEV2_PlayerState* PS = Weak.Get();
        if (!PS)
        {
            continue; 
        }
 
        if (!PS->IsDead())
        {
            ++Alive;
            LastAlive = PS;
        }
    }
 
  
   
    const bool bSolo = MatchParticipants.Num() == 1;
    const bool bRoundOver = bSolo ? (Alive == 0) : (Alive <= 1);
 
    if (bRoundOver)
    {
        FinishRound(static_cast<nullptr_t>(Alive == 1 ? LastAlive : nullptr));
    }
}
 
void APEV2_GameMode::FinishRound(nullptr_t Winner)
{
    APEV2_GameState* GS = GetGameState<APEV2_GameState>();
    if (!GS)
    {
        return;
    }
 
  
    GS->SetWinner(Winner);
    GS->SetPhase(EPEV2Phase::Ended);
 
   
    GetWorldTimerManager().SetTimer(ReturnToLobbyTimer, this, &APEV2_GameMode::ResetToLobby, ReturnToLobbyDelay, false);
}
 
void APEV2_GameMode::ResetToLobby()
{
    APEV2_GameState* GS = GetGameState<APEV2_GameState>();
    if (!GS)
    {
        return;
    }
 
 
    for (APlayerState* Player : GS->PlayerArray)
    {
        if (APEV2_PlayerState* PS = Cast<APEV2_PlayerState>(Player))
        {
            PS->SetDead(false);
        }
    }
 
    MatchParticipants.Empty();
    TeleportPlayersToBalcony();
 
    GS->SetWinner(nullptr);
    GS->SetPhase(EPEV2Phase::Lobby);
}
 
void APEV2_GameMode::TeleportPlayersToArena()
{
  
    TArray<AActor*> ArenaPoints;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), ArenaSpawnTag, ArenaPoints);
 
    if (ArenaPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No hay actores con la etiqueta '%s' en el mapa."), *ArenaSpawnTag.ToString());
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 6.0f, FColor::Red,
                FString::Printf(TEXT("Faltan puntos de la arena: poné TargetPoints con la etiqueta '%s'"), *ArenaSpawnTag.ToString()));
        }
        return;
    }
 
    TeleportPlayersToPoints(ArenaPoints);
}
 
void APEV2_GameMode::TeleportPlayersToBalcony()
{
 
    TArray<AActor*> BalconyPoints;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), BalconyPoints);
 
    if (BalconyPoints.Num() == 0)
    {
        UE_LOG(LogTemp, Warning, TEXT("No hay PlayerStart en el mapa para volver al Balcón."));
        return;
    }
 
    TeleportPlayersToPoints(BalconyPoints);
}
 
void APEV2_GameMode::TeleportPlayersToPoints(const TArray<AActor*>& Points)
{
    if (Points.Num() == 0)
    {
        return;
    }
 
    int32 Index = 0;
    for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
    {
        APlayerController* PC = It->Get();
        APawn* Pawn = PC ? PC->GetPawn() : nullptr;
        if (!Pawn)
        {
            continue;
        }
 
       
        const AActor* Target = Points[Index % Points.Num()];
        const FVector Location = Target->GetActorLocation() + FVector(0.f, 0.f, 100.f); 
        const FRotator Rotation = Target->GetActorRotation();
 
        if (!Pawn->TeleportTo(Location, Rotation))
        {
           
            Pawn->SetActorLocationAndRotation(Location, Rotation, false, nullptr, ETeleportType::TeleportPhysics);
        }
 
        ++Index;
    }
}
 