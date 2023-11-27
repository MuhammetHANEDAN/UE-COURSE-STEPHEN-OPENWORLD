// Fill out your copyright notice in the Description page of Project Settings.


#include "Breakable/BreakableActor.h"

#include "Components/CapsuleComponent.h"
#include "GeometryCollection/GeometryCollectionComponent.h"
#include "Items/Pickables/Treasure.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABreakableActor::ABreakableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	GeometryCollectionComponent=CreateDefaultSubobject<UGeometryCollectionComponent>("GeomertyCollection");
	SetRootComponent(GeometryCollectionComponent);

	GeometryCapsuleComponent=CreateDefaultSubobject<UCapsuleComponent>("GeometryCapsule");
	GeometryCapsuleComponent->SetupAttachment(GeometryCollectionComponent);
	GeometryCapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECR_Block);
	
	GeometryCollectionComponent->SetGenerateOverlapEvents(true);
	GeometryCollectionComponent->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);
	GeometryCollectionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera,ECollisionResponse::ECR_Ignore);
	GeometryCollectionComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECR_Ignore);
	
}

void ABreakableActor::GetHit_Implementation(const FHitResult& HitResult,float Damage)
{
	if(bBroken==true) return;
	bBroken=true;
	if(BreakSounds)
	{
		UGameplayStatics::PlaySoundAtLocation(this,BreakSounds,GetActorLocation());
	}
	if(GetWorld() && TreasureClases.Num()>0)
	{
		int32 Random = FMath::RandRange(0,TreasureClases.Num()-1);
		ATreasure* Treasure =GetWorld()->SpawnActor<ATreasure>(TreasureClases[Random],GetActorTransform());
		Treasure->AddActorLocalOffset(FVector(0,0,100.f),true);
		Treasure->SetItemState(EItemState::EIS_Hovering);
	}
	GeometryCapsuleComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn,ECR_Ignore);
	SetLifeSpan(2.f);
}


// Called when the game starts or when spawned
void ABreakableActor::BeginPlay()
{
	Super::BeginPlay();
	//GeometryCollectionComponent->OnChaosBreakEvent.AddDynamic(this,)
}

// Called every frame
void ABreakableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

