// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashAnimInstance.h"
#include "Characters/SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USlashAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character=Cast<ASlashCharacter>(TryGetPawnOwner());
	if(Character)
	{
		MovementComponent=Character->GetCharacterMovement();
	}
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if(Character==nullptr) return;
	if(MovementComponent)
	{
		GroundSpeed=UKismetMathLibrary::VSizeXY(MovementComponent->Velocity);
		bIsFalling=MovementComponent->IsFalling();
	}
	
}
