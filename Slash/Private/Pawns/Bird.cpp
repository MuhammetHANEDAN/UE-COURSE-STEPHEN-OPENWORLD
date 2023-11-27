// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Bird.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


// Sets default values
ABird::ABird()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent=CreateDefaultSubobject<UCapsuleComponent >(TEXT("Capsule"));
	RootComponent=CapsuleComponent;
	BirdMeshComponent=CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdMesh"));
	BirdMeshComponent->SetupAttachment(RootComponent);
	//AutoPossessPlayer = EAutoReceiveInput::Player0;
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);


}

// Called when the game starts or when spawned
void ABird::BeginPlay()
{
	Super::BeginPlay();
	if(APlayerController* PlayerController=Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem= ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(BirdMappingContext,0);
		}
	}
	if(GetController())
	{
		bUseControllerRotationPitch=true;
		bUseControllerRotationYaw=true;
	}
}	

// Called every frame
void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ABird::Move);
		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ABird::Look);
	}
}


void ABird::Move(const FInputActionValue& Value)
{
	//FVector2d MovementVector=FInputActionValue::Get<FVector2d>();
	//AddMovementInput(GetActorForwardVector(),MovementVector.X);
	UE_LOG(LogTemp,Warning,TEXT("woking"));
}

void ABird::Look(const FInputActionValue& Value)
{
	FVector2d LookAxis = Value.Get<FVector2d>();
	if(GetController()==nullptr) return;
	AddControllerPitchInput(LookAxis.Y);
	AddControllerYawInput(LookAxis.X);
}

