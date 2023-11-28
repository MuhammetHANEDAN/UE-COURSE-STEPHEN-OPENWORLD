// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"
#include "InputActionValue.h"
#include "GameFramework/SpringArmComponent.h"
#include "Characters/EnumTypes.h"
#include "Pawns/BasePawn.h"
#include "SlashCharacter.generated.h"

class USlashOverlay;
class ASlashHUD;
class AWeapon;
class AItem;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class SLASH_API ASlashCharacter : public ABaseCharacter 
{
	GENERATED_BODY()

public:
	// VARIABLES

	//FUNCTIONS
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	virtual void GetDamage(const FName& SectionName = FName(" "), const FHitResult HitResult= FHitResult(), const float Damage=0);

protected:
	// VARIABLES--------------------------
	//INPUTS
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Inputs")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Inputs")
	UInputAction* MoveAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Inputs")
	UInputAction* LookAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Inputs")
	UInputAction* JumpAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Inputs")
	UInputAction* InteractionAction;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Inputs")
	UInputAction* AttackActions;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Inputs")
	UInputAction* ArmDisarmAction;

	//HUD

	UPROPERTY()
	ASlashHUD* SlashHUD;

	UPROPERTY()
	USlashOverlay* SlashOverlay;

	//TIMERS

	FTimerHandle Delay;

	UFUNCTION()
	void InitializeSlashOverlayWidget();

	//Player Controller

	UPROPERTY()
	APlayerController* PlayerController;

	// ENUMS
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Enums)
	ECharacterStates CharacterState= ECharacterStates::ECS_Unequipped;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Enums)
	EActionStates CharacterActionState = EActionStates::EAS_Unocuppied;

	//WEAPONS
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Weapons)
	AWeapon* MainWeapon;

	/*
	* MONTAGES
	*/
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Montages)
	UAnimMontage* ArmingAnimation;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category=Montages)
	UAnimMontage* DisArmingAnimation;
	
	//FUNCTIONS-------------------------------------
	virtual void BeginPlay() override;
	
	/*
	* MONTAGES
	*/
	virtual void PlayNormalAttackMontage();
	//CHARACTER
	virtual void NormalAttack();
	virtual void ArmDisarm();

	//INPUTS
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void Jump() override;
	virtual void StopJumping() override;
	void EKeyPressed(const FInputActionValue& Value);

private:
	// COMPONENTS
	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	UAttributeComponent* AttributesComponent;

	//Variables
	/**
	 * sockets
	 */
	UPROPERTY(EditDefaultsOnly,Category=Sockets)
	FName GlaiveAttachSocketName;

	UPROPERTY(EditDefaultsOnly,Category=Sockets)
	FName GlaiveHandSocketName;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;


public:
	FORCEINLINE FName GetGlaiveAttachSocketName() const {return GlaiveAttachSocketName;}
	FORCEINLINE FName GetGlaiveHandSocketName() const {return GlaiveHandSocketName;}
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem=Item; }
	FORCEINLINE ECharacterStates GetCharacterState() const { return CharacterState;}
	FORCEINLINE void SetCharacterState(const ECharacterStates& State) { CharacterState=State;}
	FORCEINLINE EActionStates GetCharacterActionState() const  {return CharacterActionState;}
	FORCEINLINE void SetActionState(const EActionStates& State) { CharacterActionState=State;}
	FORCEINLINE AWeapon* GetMainWeapon() const { return MainWeapon;}

	bool CanPlayerPerformNormalAttack() const ;
	bool CanPlayerPerformJump() const ;
	bool CanPlayerPerformArmOrDisarm() const ;
};
