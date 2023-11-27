// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Characters/EnumTypes.h"
#include "Weapon.generated.h"

/**
 * 
 */

class UWeaponTraceComponent;
class UBoxComponent;

UCLASS()
class SLASH_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	void Equip(USceneComponent* InParent,const FAttachmentTransformRules TransformRules,const FName SocketName);

protected:
	virtual void BeginPlay() override;
	
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult) override;
	
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

	UFUNCTION()
	virtual void OnBoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	//VARIABLES

	//ENUMS
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category=Enums)
	EWeaponTypes WeaponType= EWeaponTypes::EWT_OneHandGlaive;
private:
    //COMPONENTS
    UPROPERTY(VisibleAnywhere,Category="Weapon Properties")
    UBoxComponent* BoxComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite, Category="Weapon Properties",meta=(AllowPrivateAccess="true"))
	USceneComponent* BoxStartComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Weapon Properties",meta=(AllowPrivateAccess="true"))
	USceneComponent* BoxEndComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Weapon Properties",meta=(AllowPrivateAccess="true"))
	UWeaponTraceComponent* WeaponTraceComponent;
    
public:
	//VARIABLES

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Weapon Properties")
	float WeaponDamage= 15;

	// FUNCTIONS

	//BP EVENTS
	UFUNCTION(BlueprintImplementableEvent)
	void CreateFields(const FVector& FieldLocation); 

	FORCEINLINE EWeaponTypes GetWeaponType() const {return WeaponType;}
	FORCEINLINE USceneComponent* GetBoxStartComponent() const {return BoxStartComponent;}
	FORCEINLINE USceneComponent* GetBoxEndComponent() const {return BoxEndComponent;}
};
