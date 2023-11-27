// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ArmDisarmNotify.generated.h"

/**
 * 
 */
UCLASS()
class SLASH_API UArmDisarmNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category= Initialize)
	bool bIsArming;
};
