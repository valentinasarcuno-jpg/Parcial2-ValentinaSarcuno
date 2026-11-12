// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
 
#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "PEV2_PlayerState.generated.h"
 
UCLASS()
class PARCIAL2_API APEV2_PlayerState : public APlayerState
{
	GENERATED_BODY()
 
public:
	APEV2_PlayerState();
 
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
 

	void SetDead(bool bNewDead);
	void SetSurvivalTime(float NewTime);
 
	
	UFUNCTION(BlueprintPure, Category = "Estado")
	bool IsDead() const { return bIsDead; }
 
	
	UFUNCTION(BlueprintPure, Category = "Estado")
	float GetSurvivalTime() const { return SurvivalTime; }
 
protected:
	
	UPROPERTY(ReplicatedUsing = OnRep_IsDead)
	bool bIsDead;
 
	
	UPROPERTY(Replicated)
	float SurvivalTime;
 
	
	UFUNCTION()
	void OnRep_IsDead();
 
private:
	
	void NotifyListChanged();
};
 