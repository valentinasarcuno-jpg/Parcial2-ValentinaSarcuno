// Fill out your copyright notice in the Description page of Project Settings.
 
 
#include "A_Laser.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Framework/PEV2_GameState.h"
#include "Framework/PEV2_PlayerState.h"
 
// Sets default values
AA_Laser::AA_Laser()
{
    PrimaryActorTick.bCanEverTick = true;
 
    
    bReplicates = true;
    
    SetReplicatingMovement(true);
 
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    RootComponent = CollisionBox;
    CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
 
    LaserMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserMesh"));
    LaserMesh->SetupAttachment(RootComponent);
    LaserMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
 
    MoveSpeed = 400.0f;
    MoveDirection = FVector(1.0f, 0.0f, 0.0f);
 
   
    InitialLifeSpan = 10.0f;
}
 
// Called when the game starts or when spawned
void AA_Laser::BeginPlay()
{
    Super::BeginPlay();
 
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AA_Laser::OnOverlapBegin);
}
 
// Called every frame
void AA_Laser::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
 
   
    if (!HasAuthority())
    {
        return;
    }
 
    FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * MoveSpeed * DeltaTime);
    SetActorLocation(NewLocation);
}
 
void AA_Laser::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    
    if (!HasAuthority())
    {
        return;
    }
 
    if (!OtherActor || OtherActor == this)
    {
        return;
    }
 
    ACharacter* HitPlayer = Cast<ACharacter>(OtherActor);
    if (!HitPlayer)
    {
        return;
    }
 
   
    const APEV2_GameState* GS = GetWorld()->GetGameState<APEV2_GameState>();
    if (!GS || GS->GetPhase() != EPEV2Phase::Playing)
    {
        return;
    }
 
 
    APEV2_PlayerState* PS = HitPlayer->GetPlayerState<APEV2_PlayerState>();
    if (PS && !PS->IsDead())
    {
        PS->SetDead(true);
    }
}
 