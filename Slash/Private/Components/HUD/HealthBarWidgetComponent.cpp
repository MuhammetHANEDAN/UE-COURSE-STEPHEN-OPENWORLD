// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/HUD/HealthBarWidgetComponent.h"

#include "Components/ProgressBar.h"
#include "HUD/HealthBar.h"

void UHealthBarWidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	HealthBarWidget=Cast<UHealthBar>(GetUserWidgetObject());
	if(HealthBarWidget && HealthBarWidget->HealthBar )
	{
		HealthBarWidget->HealthBar->SetPercent(1.f);
	}
	
}

void UHealthBarWidgetComponent::SetHealthPercent(float Percent)
{
	if(HealthBarWidget && HealthBarWidget->HealthBar)
	{
		HealthBarWidget->HealthBar->SetPercent(Percent);
	}
}
