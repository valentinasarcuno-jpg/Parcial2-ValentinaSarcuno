// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_LaserSpawner.generated.h"

class UBoxComponent;
class AA_Laser;

UCLASS()
class PARCIAL2_API AA_LaserSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_LaserSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	TSubclassOf<AA_Laser> LaserClassToSpawn;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float MinSpawnTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawner")
	float MaxSpawnTime;

	FTimerHandle SpawnTimerHandle;

	UFUNCTION()
	void ScheduleNextSpawn();

	UFUNCTION()
	void SpawnLaser();
};