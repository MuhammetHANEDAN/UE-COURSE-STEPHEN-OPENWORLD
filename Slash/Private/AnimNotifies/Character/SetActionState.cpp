// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/Character/SetActionState.h"
#include "Characters/SlashCharacter.h"



void USetActionState::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	const FAnimNotifyEventReference& EventReference)
{
	Super::Notify(MeshComp, Animation, EventReference);
	if(ASlashCharacter* PlayerCharacter =Cast<ASlashCharacter>(MeshComp->GetOwner()))
	{
		PlayerCharacter->SetActionState(EActionStates::EAS_Unocuppied);
	}
	
}
