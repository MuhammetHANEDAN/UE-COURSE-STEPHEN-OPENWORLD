// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Item.h"
#include <string>
#include "Characters/SlashCharacter.h"
#include "Components/SphereComponent.h"
#include "Slash/DebugMacros.h"



// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMeshComponent"));
	RootComponent=ItemMesh;
	SphereComponent=CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComponent->SetupAttachment(ItemMesh);
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AItem::OnSphereBeginOverlap);
	SphereComponent->OnComponentEndOverlap.AddDynamic(this,&AItem::OnSphereEndOverlap);
}

void AItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ASlashCharacter* PlayerCharacter = Cast<ASlashCharacter>(OtherActor))
	{
		PlayerCharacter->SetOverlappingItem(this);
	}
}

void AItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(ASlashCharacter* PlayerCharacter = Cast<ASlashCharacter>(OtherActor))
	{
		PlayerCharacter->SetOverlappingItem(nullptr);
	}
}

// Called every frame  note tick deactivated
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(ItemState==EItemState::EIS_Hovering)
	{
		RunningTime +=DeltaTime;
		AddActorWorldOffset(FVector(0,0,GetTransformedSin())*DeltaTime);
		DRAW_SPHERE_SingleFrame(GetActorLocation());
		DRAW_VECTOR_SingleFrame(GetActorLocation(),GetActorLocation()+GetActorForwardVector()*100);
	}
}

float AItem::GetTransformedSin() const
{
	return Amplitude*FMath::Sin(RunningTime*TimeConstant);
}




