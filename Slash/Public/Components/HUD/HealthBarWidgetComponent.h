// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "HealthBarWidgetComponent.generated.h"

class UHealthBar;
/**
 * 
 */
UCLASS()
class SLASH_API UHealthBarWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void SetHealthPercent(float Percent);
private:
	UPROPERTY()
	UHealthBar* HealthBarWidget;
};
