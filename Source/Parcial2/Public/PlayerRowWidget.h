// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
 
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerRowWidget.generated.h"
 
class UTextBlock;
class UBorder;
class UImage;
 
UCLASS()
class PARCIAL2_API UPlayerRowWidget : public UUserWidget
{
	GENERATED_BODY()
 
public:
	
	void SetData(const FString& PlayerName, bool bFallen, float TimeSeconds);
 
protected:
	
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* TXT_PlayerName;
 
	UPROPERTY(meta = (BindWidgetOptional))
	UTextBlock* TXT_AliveTime;
 

 
	UPROPERTY(meta = (BindWidgetOptional))
	UImage* RowImage;
 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Colores")
	FLinearColor AliveColor = FLinearColor::White;
 
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Colores")
	FLinearColor FallenColor = FLinearColor(1.0f, 0.15f, 0.15f, 1.0f);
};
 