// Fill out your copyright notice in the Description page of Project Settings.


#include "A_Laser.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "Engine/Engine.h"

// Sets default values
AA_Laser::AA_Laser()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	RootComponent = CollisionBox;
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));


	LaserMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LaserMesh"));
	LaserMesh->SetupAttachment(RootComponent);
	LaserMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision); 


	MoveSpeed = 400.0f;
	MoveDirection = FVector(1.0f, 0.0f, 0.0f); 
	
	// Tiempo para destruir el lAEERRser))
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

	
	FVector NewLocation = GetActorLocation() + (GetActorForwardVector() * MoveSpeed * DeltaTime);
	SetActorLocation(NewLocation);
}

void AA_Laser::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (OtherActor && OtherActor != this)
	{
		ACharacter* HitPlayer = Cast<ACharacter>(OtherActor);
		if (HitPlayer)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("¡EL JUGADOR FUE ELIMINADO!"));
			
			
			HitPlayer->Destroy();
		}
	}
}

