// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

class UCameraComponent;
class USpringArmComponent;
struct FInputActionValue;
class UInputAction;
class UCapsuleComponent;
class UInputMappingContext;

UCLASS()
class SLASH_API ABird : public APawn
{
	GENERATED_BODY()

public:
	ABird();
	virtual void Tick(float DeltaTime) override;
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
protected:
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	//VARIABLES ---------
	
	//INPUTS
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input")
	UInputMappingContext* BirdMappingContext;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input")
	UInputAction* LookAction;

	//FUNCTIONS -----

	//INPUTS
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
private:
	//COMPONENTS
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* BirdMeshComponent;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;
	//--------
};
