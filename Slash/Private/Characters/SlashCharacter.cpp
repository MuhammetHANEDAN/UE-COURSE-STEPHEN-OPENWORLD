// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/SlashAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Items/Weapons/Weapon.h"
#include "Characters/EnumTypes.h" 
#include "Components/SphereComponent.h"

ASlashCharacter::ASlashCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	
	
	SpringArmComponent=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	CameraComponent=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);


	
}

// Called when the game starts or when spawned
void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	GetMesh()->HideBoneByName(TEXT("weapon"),PBO_None);
	if(APlayerController* PlayerController= Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem=ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext,0);
		}
	}
	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch=false;
	bUseControllerRotationRoll=false;
	SpringArmComponent->bUsePawnControlRotation=true;
	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate.Yaw=300;
}

// Called every frame
void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// ------ INPUTS
void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if(UEnhancedInputComponent* EnhancedInputComponent=CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ASlashCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction,ETriggerEvent::Triggered,this,&ASlashCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Triggered,this,&ASlashCharacter::Jump);
		EnhancedInputComponent->BindAction(InteractionAction,ETriggerEvent::Started,this,&ASlashCharacter::EKeyPressed);
		EnhancedInputComponent->BindAction(AttackActions,ETriggerEvent::Started,this,&ASlashCharacter::NormalAttack);
		EnhancedInputComponent->BindAction(ArmDisarmAction,ETriggerEvent::Started,this,&ASlashCharacter::ArmDisarm);
	}
}


void ASlashCharacter::Move(const FInputActionValue& Value)
{
	const FVector2d MoveVector = Value.Get<FVector2d>();
	const FRotator Rotation=GetControlRotation();
	const FRotator RotationDirection = FRotator(0,Rotation.Yaw,0);
	const FVector DirectionVector=FRotationMatrix(RotationDirection).GetUnitAxis(EAxis::X);
	const FVector RigtVector= FRotationMatrix(RotationDirection).GetUnitAxis(EAxis::Y);
	AddMovementInput(DirectionVector,MoveVector.Y);
	AddMovementInput(RigtVector,MoveVector.X);
}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
	const FVector2d LookVector = Value.Get<FVector2d>();
	AddControllerYawInput(LookVector.X);
	AddControllerPitchInput(LookVector.Y);
}

void ASlashCharacter::Jump()
{
	if(CanPlayerPerformJump())
	{
		Super::Jump();
	}
	/*CharacterActionState=EActionStates::EAS_JumpingOrFalling;
	UE_LOG(LogTemp,Warning,TEXT(" jumped"));*/
}

void ASlashCharacter::StopJumping()
{
	Super::StopJumping();
	/*CharacterActionState=EActionStates::EAS_Unocuppied;
	UE_LOG(LogTemp,Warning,TEXT(" jump stopped"));*/
}


//-----------

//CHARACTER
void ASlashCharacter::EKeyPressed(const FInputActionValue& Value)
{
	if(AWeapon* Weapon=Cast<AWeapon>(OverlappingItem))
	{
		const FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget,true);
		if(MainWeapon != nullptr) return;
		Weapon->Equip(GetMesh(),TransformRules,GetGlaiveAttachSocketName());
		MainWeapon=Weapon;
		Weapon->GetSphereComponent()->SetCollisionEnabled((ECollisionEnabled::NoCollision));
	}
}

bool ASlashCharacter::CanPlayerPerformNormalAttack() const
{
	const bool bEquipped = CharacterState != ECharacterStates::ECS_Unequipped;
	const bool bNotAttacking = CharacterActionState != EActionStates::EAS_Attacking;
	const bool bNotEquipping = CharacterActionState != EActionStates::EAS_Equipping;
	const bool bNotDodging = CharacterActionState != EActionStates::EAS_Dodging;
	const bool bNotJumpOrFalling = !(GetMovementComponent()->IsFalling());
	if(bEquipped && bNotAttacking &&  bNotEquipping && bNotDodging && bNotJumpOrFalling)
	{
		return true;
	}
	return false;
}

bool ASlashCharacter::CanPlayerPerformJump() const
{
	const bool bNotAttacking = CharacterActionState != EActionStates::EAS_Attacking;
	const bool bNotEquipping = CharacterActionState != EActionStates::EAS_Equipping;
	const bool bNotDodging = CharacterActionState != EActionStates::EAS_Dodging;
	const bool bNotJumpOrFalling = !(GetMovementComponent()->IsFalling());
	if(bNotAttacking &&  bNotEquipping && bNotDodging && bNotJumpOrFalling)
	{
		return true;
	}
	return false;
}

bool ASlashCharacter::CanPlayerPerformArmOrDisarm() const
{
	const bool bNotAttacking = CharacterActionState != EActionStates::EAS_Attacking;
	const bool bNotEquipping = CharacterActionState != EActionStates::EAS_Equipping;
	const bool bNotDodging = CharacterActionState != EActionStates::EAS_Dodging;
	const bool bNotJumpOrFalling = !(GetMovementComponent()->IsFalling());
	if(MainWeapon && bNotAttacking &&  bNotEquipping && bNotDodging && bNotJumpOrFalling)
	{
		return true;
	}
	return false;
}


void ASlashCharacter::PlayNormalAttackMontage()
{
	if(CharacterState!=ECharacterStates::ECS_Unequipped && AttackMontage && GetMesh()->GetAnimInstance())
	{
		CharacterActionState=EActionStates::EAS_Attacking;
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage,1,EMontagePlayReturnType::MontageLength);
	}
}

void ASlashCharacter::NormalAttack()
{
	if(CanPlayerPerformNormalAttack())
	{
		PlayNormalAttackMontage();
	}
}

void ASlashCharacter::ArmDisarm()
{
	if(CanPlayerPerformArmOrDisarm()==false) return;
	if(CharacterState==ECharacterStates::ECS_Unequipped)
	{
		GetMesh()->GetAnimInstance()->Montage_Play(ArmingAnimation);
	}
	else
	{
		GetMesh()->GetAnimInstance()->Montage_Play(DisArmingAnimation);
	}
	
}



