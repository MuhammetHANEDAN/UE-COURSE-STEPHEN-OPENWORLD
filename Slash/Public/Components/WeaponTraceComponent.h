// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponTraceComponent.generated.h"


class AWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SLASH_API UWeaponTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponTraceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//Variables
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Initialize")
	float WeaponTraceRadius=20;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void EnableTrace();
	void DisableTrace();

	//VARIABLES
	bool bTraceEnabled = false;
	AWeapon* OwnerWeapon; 
	TArray<AActor*>HittedActors;
	
private:
	
	
	
		
};
