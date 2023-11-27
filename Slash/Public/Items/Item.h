// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;

UENUM(BlueprintType)
enum class EItemState
{
	EIS_None UMETA(DisplayName="None"),
	EIS_InInventory UMETA(DisplayName="InInventory"),
	EIS_Hovering UMETA(DisplayName="Hovering"),
	EIS_Attached UMETA(DisplayName="Attached"),
	EIS_Armed UMETA(DisplayName="Armed"),
};

UCLASS()
class SLASH_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:

	//COMPONENTS
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* ItemMesh;
    
	UPROPERTY(VisibleAnywhere)
	USphereComponent* SphereComponent;

	//Variables-------------------
	
	//Variables for Sin Movement
	UPROPERTY(EditAnywhere,Category="Sin Movement")
	float Amplitude=10.f;

	UPROPERTY(EditAnywhere,Category="Sin Movement")
	float TimeConstant=5.f;

	//Enums
	// For hovering you can change this to Hovering 
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Enums")
	EItemState ItemState;
	
	//SAMPLES
	template<typename T>
	T Avg(T first,T second);
	
	//FUNCTIONS---------------

	UFUNCTION(BlueprintCallable)
	float GetTransformedSin() const ;
private:
	//Variables for Sin Movement
	UPROPERTY(VisibleAnywhere)
	float RunningTime;
	
	//----------
public:
	FORCEINLINE USphereComponent* GetSphereComponent() { return SphereComponent;}
	FORCEINLINE void SetItemState(const EItemState& State) { ItemState=State;}
};
