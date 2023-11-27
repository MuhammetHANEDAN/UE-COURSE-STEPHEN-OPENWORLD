// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WeaponTraceComponent.h"
#include "Characters/SlashCharacter.h"
#include "Interfaces/HitInterface.h"
#include "Items/Weapons/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values for this component's properties
UWeaponTraceComponent::UWeaponTraceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponTraceComponent::BeginPlay()
{
	Super::BeginPlay();
	OwnerWeapon=Cast<AWeapon>(GetOwner());
	// ...
	
}


// Called every frame
void UWeaponTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bTraceEnabled==false) return;
	if(OwnerWeapon==nullptr) return;
	FVector Start=OwnerWeapon->GetBoxStartComponent()->GetComponentLocation();
	FVector End=OwnerWeapon->GetBoxEndComponent()->GetComponentLocation();
	TArray<AActor*> ActorsToIgnore;
	ASlashCharacter* PlayerCharacter = Cast<ASlashCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(),0));
	ActorsToIgnore.Add(PlayerCharacter);
	ActorsToIgnore.Add(OwnerWeapon);
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Visibility));
	ObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_Destructible));
	TArray<FHitResult> HitResults;
	bool bHitted =UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(),Start,End,WeaponTraceRadius,
		ObjectTypes,false,
		ActorsToIgnore,EDrawDebugTrace::ForDuration,HitResults,true);
	for (const FHitResult& HitResult : HitResults)
	{
		AActor* HitActor=HitResult.GetActor();
		if(!(HittedActors.Contains(HitActor)))
		{
			HittedActors.AddUnique(HitActor);
			if(IHitInterface* HitInterface=Cast<IHitInterface>(HitActor))
			{
				HitInterface->Execute_GetHit(HitActor,HitResult,OwnerWeapon->WeaponDamage);
				HitInterface->GetHit_Implementation(HitResult,OwnerWeapon->WeaponDamage);
			}
		}
	}
	
	// ...
}

void UWeaponTraceComponent::EnableTrace()
{
	bTraceEnabled=true;
	OwnerWeapon=Cast<AWeapon>(GetOwner());
}

void UWeaponTraceComponent::DisableTrace()
{
	bTraceEnabled=false;
	HittedActors.Empty();
}



