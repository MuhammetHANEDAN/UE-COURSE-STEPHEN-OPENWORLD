// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/BasePawn.h"

#include "Components/AttributeComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Slash/DebugMacros.h"
#include "Slash/Public/Components/HUD/HealthBarWidgetComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent=CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	RootComponent=CapsuleComponent;
	//CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CapsuleComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
	//CapsuleComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
	//CapsuleComponent->SetCollisionProfileName(FName("Pawn"));
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);
	CapsuleComponent->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);

	
	SkeletalMeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SkeletalMeshComponent->SetCollisionObjectType(ECC_Pawn);
	SkeletalMeshComponent->SetCollisionResponseToChannel(ECC_Camera,ECR_Ignore);

	AttributesComponent=CreateDefaultSubobject<UAttributeComponent>("Attributes");

	HealthBarWidgetComponent=CreateDefaultSubobject<UHealthBarWidgetComponent>("HealthBarWidget");
	HealthBarWidgetComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

//COMBAT ------------------------

//SFX----------
void ABasePawn::ApplySoundEffects(const FVector& Location)
{
	if(HitSound==nullptr) return;
	UGameplayStatics::PlaySoundAtLocation(this,HitSound,Location);
}

void ABasePawn::ApplyParticleEffects(const FVector& Location)
{
	if(HitParticles == nullptr) return;
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(),HitParticles,Location);
}

// CONDITION CHECKS
bool ABasePawn::CanGetDamage() const //*
{
	return true; //*
}
//GENERAL

void ABasePawn::PlayHitReactMontages(const FName& SectionName)
{
	UAnimInstance* AnimInstance = SkeletalMeshComponent->GetAnimInstance();
	if(AnimInstance && HitReactMontages)
	{
		AnimInstance->Montage_Play(HitReactMontages);
		AnimInstance->Montage_JumpToSection(SectionName,HitReactMontages);
		
	}
}

void ABasePawn::GetDamage(const FName& SectionName, const FHitResult HitResult, const float Damage)
{
	PlayHitReactMontages(SectionName);
	ApplySoundEffects(HitResult.ImpactPoint);
	ApplyParticleEffects(HitResult.ImpactPoint);
	AttributesComponent->Health=FMath::Clamp(AttributesComponent->Health-Damage,0,AttributesComponent->MaxHealth);
	if(HealthBarWidgetComponent)
	{
		HealthBarWidgetComponent->SetHealthPercent(AttributesComponent->Health/AttributesComponent->MaxHealth);
		float CurrentHealth=AttributesComponent->Health/AttributesComponent->MaxHealth;
		if(AttributesComponent->IsAlive()==false && DeathMontage)
		{
			SkeletalMeshComponent->GetAnimInstance()->Montage_Play(DeathMontage);
		}
	}

}

void ABasePawn::GetHit_Implementation(const FHitResult& HitResult,float Damage)
{
	if(CanGetDamage())
	{
		const FString Name=GetName();//
		UE_LOG(LogTemp,Warning,TEXT("%s got damaged"),*Name);
		DRAW_SPHERE(HitResult.ImpactPoint);//

		FVector ForwardVector =GetActorForwardVector();
		FVector ImpactVector = (HitResult.ImpactPoint-GetActorLocation()).GetSafeNormal();
		const double ChosTheta =FVector::DotProduct(ForwardVector,ImpactVector);
		float Theta =FMath::Acos(ChosTheta);
		Theta = FMath::RadiansToDegrees(Theta);
		FVector CrossVector =FVector::CrossProduct(ForwardVector,ImpactVector);
		if(CrossVector.Z <0)
		{
			Theta *=-1.f;
		}
		FName Direction = FName("Back");
		/*switch (Theta) // çalışmadı sonradan bak
		{
		case (Theta > 45 && Theta<135):
			Direction=FName("Right");
			break;
		case (Theta>-135 && Theta<-45):
			Direction=FName("Left");
			break;
		};*/
		if(Theta<45 && Theta >=-45)
		{
			Direction = FName("Forward");
		}
		else if(Theta >= 45 && Theta<135)
		{
			Direction=FName("Right");
		}
		else if(Theta>=-135 && Theta<-45)
		{
			Direction=FName("Left");
		}
		
		GetDamage(Direction,HitResult,Damage);
	}
}

