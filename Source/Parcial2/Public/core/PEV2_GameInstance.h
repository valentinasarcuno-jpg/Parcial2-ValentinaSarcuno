// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
 
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "PEV2_GameInstance.generated.h"
 
UCLASS()
class PARCIAL2_API UPEV2_GameInstance : public UGameInstance
{
	GENERATED_BODY()
 
public:
	void SetDesiredPlayerName(const FString& NewName) { DesiredPlayerName = NewName; }
	const FString& GetDesiredPlayerName() const { return DesiredPlayerName; }
 
private:
	
	UPROPERTY()
	FString DesiredPlayerName;
};
 