// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerRowWidget.h"
 
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
 
void UPlayerRowWidget::SetData(const FString& PlayerName, bool bFallen, float TimeSeconds)
{
	if (TXT_PlayerName)
	{
		TXT_PlayerName->SetText(FText::FromString(PlayerName));
	}
 
	if (TXT_AliveTime)
	{
		if (TimeSeconds < 0.0f)
		{
			TXT_AliveTime->SetText(FText::FromString(TEXT("--:--")));
		}
		else
		{
			const int32 TotalSeconds = FMath::FloorToInt(TimeSeconds);
			TXT_AliveTime->SetText(FText::FromString(
				FString::Printf(TEXT("%02d:%02d"), TotalSeconds / 60, TotalSeconds % 60)));
		}
	}
 

	const FLinearColor& Color = bFallen ? FallenColor : AliveColor;
 

 
	if (RowImage)
	{
		RowImage->SetColorAndOpacity(Color);
	}
}
 