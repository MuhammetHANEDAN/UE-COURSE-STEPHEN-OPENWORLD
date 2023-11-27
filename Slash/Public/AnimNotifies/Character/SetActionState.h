// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Characters/EnumTypes.h"
#include "SetActionState.generated.h"

/**
 * 
 */
UCLASS()
class SLASH_API USetActionState : public UAnimNotify
{
	GENERATED_BODY()
	//bool Received_Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) const;
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
public:
	//VARIABLES
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	EActionStates ActionState;
	//FUNCTION
	
};
