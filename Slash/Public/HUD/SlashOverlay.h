// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlashOverlay.generated.h"

class UTextBlock;
class UProgressBar;
/**
 * 
 */
UCLASS()
class SLASH_API USlashOverlay : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetHealthorStaminaPercent(float Percent,bool bIsHealth);
	void SetGoldorSouldText(int32 Count,bool bIsGold);

private:
	
	UPROPERTY(meta=(BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(meta=(BindWidget))
	UProgressBar* StaminaProgressBar;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* GoldText;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* SoulText;
};
