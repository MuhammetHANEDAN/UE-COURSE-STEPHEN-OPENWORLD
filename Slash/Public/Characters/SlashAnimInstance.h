// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Characters/EnumTypes.h"
#include "SlashAnimInstance.generated.h"

class UCharacterMovementComponent;
class ASlashCharacter;
/**
 * 
 */
UCLASS()
class SLASH_API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadWrite)
	ASlashCharacter* Character;

	UPROPERTY(BlueprintReadWrite,Category=Movement)
	UCharacterMovementComponent* MovementComponent;

	UPROPERTY(BlueprintReadWrite,Category=Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadWrite,Category=Movement)
	bool bIsFalling;

	UPROPERTY(BlueprintReadWrite,Category="Movement | Character State")
	ECharacterStates CharacterState= ECharacterStates::ECS_Unequipped;
	
	UPROPERTY(BlueprintReadWrite,Category="Movement | Character State")
	EActionStates ActionState = EActionStates::EAS_Unocuppied;
	
};
