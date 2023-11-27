#pragma once
//#include "Characters/EnumTypes.h" For this header include 
// PLAYER CHARACTER
UENUM(BlueprintType) //Character State
enum class ECharacterStates : uint8
{
	ECS_Unequipped UMETA(DisplayName="Unequipped"),
	ECS_EquippedOneHand  UMETA(DisplayName="EquippedOneHand")
};

UENUM(BlueprintType)
enum class EActionStates : uint8
{
	EAS_Unocuppied UMETA(DisplayNmae="Unocuppied"),
	EAS_Attacking UMETA(DisplayNmae="Attacking"),
	EAS_Dodging UMETA(DisplayNmae="Dodging"),
	EAS_Equipping UMETA(DisplayNmae="Equipping"),
	EAS_JumpingOrFalling UMETA(DisplayNmae="Jumping/Falling")
};

//WEAPONS
UENUM(BlueprintType) //Weapon Type
enum class EWeaponTypes : uint8
{
	EWT_OneHandSword UMETA(DisplayName="OneHandSword"),
	EWT_OneHandDagger UMETA(DisplayName="OneHandDagger"),
	EWT_OneHandGlaive UMETA(DisplayName="OneHandGlaive")
};

