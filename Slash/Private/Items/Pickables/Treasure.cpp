// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Pickables/Treasure.h"

#include "Characters/SlashCharacter.h"
#include "Kismet/GameplayStatics.h"

void ATreasure::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ASlashCharacter* PlayerCharacter = Cast<ASlashCharacter>(OtherActor))
	{
		if(PickUpSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this,PickUpSound,GetActorLocation());
		}
		Destroy();
	}
	
}
