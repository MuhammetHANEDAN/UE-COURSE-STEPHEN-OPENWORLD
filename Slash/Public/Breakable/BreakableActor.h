// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/HitInterface.h"
#include "BreakableActor.generated.h"

class UCapsuleComponent;
class ATreasure;
class UGeometryCollectionComponent;

UCLASS()
class SLASH_API ABreakableActor : public AActor , public IHitInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakableActor();
	//INTERFACES
	virtual void GetHit_Implementation(const FHitResult& HitResult,float Damage) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool bBroken=false;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere)
	UGeometryCollectionComponent* GeometryCollectionComponent;

	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* GeometryCapsuleComponent;

	//VARIABLES
	//FX
	
	UPROPERTY(EditDefaultsOnly,Category="Sounds")
	USoundBase* BreakSounds;

	UPROPERTY(EditDefaultsOnly,Category="Treasue Class")
	TArray<TSubclassOf<ATreasure>> TreasureClases;
};
