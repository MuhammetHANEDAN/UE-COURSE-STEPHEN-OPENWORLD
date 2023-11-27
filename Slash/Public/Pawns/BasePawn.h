// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interfaces/HitInterface.h"
#include "BasePawn.generated.h"

class UHealthBarWidgetComponent;
class UWidgetComponent;
class UAttributeComponent;
class UCapsuleComponent;
class USphereComponent;
UCLASS()
class SLASH_API ABasePawn : public APawn , public IHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//FUNCTIONS
	//ACTION CHECKS
	bool CanGetDamage() const ;  // *

	//VARIABLES
	
	/**
	 * MONTAGES
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Montages")
	UAnimMontage* HitReactMontages;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Montages")
	UAnimMontage* DeathMontage;

	/**
	 * SFX
	 */
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Sounds")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Effects")
	UParticleSystem* HitParticles;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//FUNCTIONS

	//SFX
	void ApplySoundEffects(const FVector& Location);
	void ApplyParticleEffects(const FVector& Location);
	
	/**
	 * MONTAGES
	 */
	virtual void PlayHitReactMontages(const FName& SectionName);

	//Combat
	virtual void GetDamage(const FName& SectionName, const FHitResult HitResult, const float Damage);

	//INTERFACES
	//HIT INTERFACE
	virtual void GetHit_Implementation(const FHitResult& HitResult,float Damage) override;

	//COMPONENTS
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* SkeletalMeshComponent;
private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* AttributesComponent;

	UPROPERTY(VisibleAnywhere)
	UHealthBarWidgetComponent* HealthBarWidgetComponent;
	
};
