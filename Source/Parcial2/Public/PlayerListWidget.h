// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
 
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Framework/PEV2_PlayerState.h"
#include "PlayerListWidget.generated.h"
 
class UVerticalBox;
class UPlayerRowWidget;
 
UCLASS()
class PARCIAL2_API UPlayerListWidget : public UUserWidget
{
	GENERATED_BODY()
 
protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
 
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* PlayerListBox;
 
	
	UPROPERTY(EditDefaultsOnly, Category = "Lista")
	TSubclassOf<UPlayerRowWidget> RowClass;
 
	
	UFUNCTION()
	void HandleListChanged();
 
private:
	bool bBoundToGameState = false;
	float UpdateAccumulator = 0.0f;
 
	
	TMap<TWeakObjectPtr<APEV2_PlayerState>, TWeakObjectPtr<UPlayerRowWidget>> Rows;
 
	void TryBindToGameState();
	void RefreshList();
};
 