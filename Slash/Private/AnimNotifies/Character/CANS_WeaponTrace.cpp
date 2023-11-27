// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/Character/CANS_WeaponTrace.h"

#include "Characters/SlashCharacter.h"
#include "Components/WeaponTraceComponent.h"
#include "Items/Weapons/Weapon.h"


void UCANS_WeaponTrace::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration,
                                    const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if(ASlashCharacter* PlayerCharacter=Cast<ASlashCharacter>(MeshComp->GetOwner()))
	{
		AWeapon* PlayerWeapon=PlayerCharacter->GetMainWeapon();
		if(PlayerWeapon==nullptr) return;
		UWeaponTraceComponent* WeaponTrace=PlayerWeapon->FindComponentByClass<UWeaponTraceComponent>();
		if(WeaponTrace== nullptr) return;
		PlayerWeaponTraceComponent=WeaponTrace;
		WeaponTrace->EnableTrace();
	}
}

void UCANS_WeaponTrace::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	if(ASlashCharacter* PlayerCharacter=Cast<ASlashCharacter>(MeshComp->GetOwner()))
	{
		if(PlayerWeaponTraceComponent==nullptr) return;
		PlayerWeaponTraceComponent->DisableTrace();
	}
}
