// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"
#include "Characters/SlashCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/WeaponTraceComponent.h"
#include "Slash/DebugMacros.h"

AWeapon::AWeapon()
{
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("Weapon Box");
	BoxComponent->SetupAttachment(GetRootComponent());
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);

	BoxStartComponent= CreateDefaultSubobject<USceneComponent>("Weapon Box Start");
	BoxStartComponent->SetupAttachment(GetRootComponent());
	BoxEndComponent= CreateDefaultSubobject<USceneComponent>("Weapon Box End");
	BoxEndComponent->SetupAttachment(GetRootComponent());

	WeaponTraceComponent=CreateDefaultSubobject<UWeaponTraceComponent>(TEXT("Weapon Trace"));
	
	
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	BoxComponent->OnComponentBeginOverlap.AddDynamic(this,&AWeapon::OnBoxComponentBeginOverlap);
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
// DELEGATES
void AWeapon::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if(ASlashCharacter* PlayerCharacter = Cast<ASlashCharacter>(OtherActor))
	{
		
	}
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
}

void AWeapon::OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*const FVector Start=BoxStartComponent->GetComponentLocation();
	const FVector End=BoxEndComponent->GetComponentLocation();
	TArray<AActor*>ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult HitResult;*/

	/*bool bhitted = UKismetSystemLibrary::BoxTraceSingle(GetWorld(),Start,End,FVector(5.f,5.f,5.f),
		Start.Rotation(),TraceTypeQuery1,false,ActorsToIgnore,EDrawDebugTrace::ForDuration,
		HitResult,true);*/

	/*if(bhitted)
	{
		//FVector impactPoint=HitResult.ImpactPoint;
		//DRAW_SPHERE(impactPoint);
	}
	*/
}

//CLASS FUNCTIONS
void AWeapon::Equip(USceneComponent* InParent,const FAttachmentTransformRules TransformRules,const FName SocketName)
{
	if(AttachToComponent(InParent,TransformRules,SocketName))
	{
		ItemState=EItemState::EIS_Attached;
	}
	SphereComponent->SetActive(false);
}


