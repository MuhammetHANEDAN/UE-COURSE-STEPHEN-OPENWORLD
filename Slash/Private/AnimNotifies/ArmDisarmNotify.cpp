// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/ArmDisarmNotify.h"

#include "Characters/SlashAnimInstance.h"
#include "Characters/SlashCharacter.h"
#include "Items/Weapons/Weapon.h"

void UArmDisarmNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                              const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if(ASlashCharacter* PlayerCharacter = Cast<ASlashCharacter>(MeshComp->GetOwner()))
	{
		AWeapon* Weapon =PlayerCharacter->GetMainWeapon();
		USlashAnimInstance* AnimInstance= Cast<USlashAnimInstance>(MeshComp->GetAnimInstance());
		if(Weapon == nullptr) return;
		if(bIsArming)
		{
			Weapon->Equip(MeshComp,FAttachmentTransformRules::SnapToTargetIncludingScale,PlayerCharacter->GetGlaiveHandSocketName());
			PlayerCharacter->SetCharacterState(ECharacterStates::ECS_EquippedOneHand);
			if(AnimInstance)
			{
				AnimInstance->CharacterState=ECharacterStates::ECS_EquippedOneHand;
			}
		}
		else
		{
			Weapon->Equip(MeshComp,FAttachmentTransformRules::SnapToTargetIncludingScale,PlayerCharacter->GetGlaiveAttachSocketName());
			PlayerCharacter->SetCharacterState(ECharacterStates::ECS_Unequipped);
			if(AnimInstance)
			{
				AnimInstance->CharacterState=ECharacterStates::ECS_Unequipped;
			}
		}
	}
}
