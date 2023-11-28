// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SlashOverlay.h"

#include <string>

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void USlashOverlay::SetHealthorStaminaPercent(const float Percent, const bool bIsHealth)
{
	if(HealthProgressBar && bIsHealth)
	{
		HealthProgressBar->SetPercent(Percent);
	}
	if(StaminaProgressBar)
	{
		StaminaProgressBar->SetPercent(Percent);
	}
}

void USlashOverlay::SetGoldorSouldText(int32 Count, bool bIsGold)
{
	if(GoldText && bIsGold)
	{
		GoldText->SetText(FText::FromString(FString::Printf(TEXT("%d"),Count)));
	}
	if(StaminaProgressBar)
	{
		SoulText->SetText(FText::FromString(FString::Printf(TEXT("%d"),Count)));
	}
}
