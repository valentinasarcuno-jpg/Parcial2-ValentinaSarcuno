// Fill out your copyright notice in the Description page of Project Settings.


#include "A_LaserSpawner.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "A_Laser.h"  

// Sets default values
AA_LaserSpawner::AA_LaserSpawner()
{
	PrimaryActorTick.bCanEverTick = false;

	
	USceneComponent* Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	
	MinSpawnTime = 1.0f;
	MaxSpawnTime = 6.0f;
}

void AA_LaserSpawner::BeginPlay()
{
	Super::BeginPlay();
	ScheduleNextSpawn(); 
}

void AA_LaserSpawner::ScheduleNextSpawn()
{
	if (LaserClassToSpawn)
	{
		
		float RandomDelay = FMath::RandRange(MinSpawnTime, MaxSpawnTime);
		
		
		GetWorldTimerManager().SetTimer(SpawnTimerHandle, this, &AA_LaserSpawner::SpawnLaser, RandomDelay, false);
	}
}

void AA_LaserSpawner::SpawnLaser()
{
	if (!LaserClassToSpawn) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	
	GetWorld()->SpawnActor<AA_Laser>(LaserClassToSpawn, GetActorLocation(), GetActorRotation(), SpawnParams);

	
	ScheduleNextSpawn();
}