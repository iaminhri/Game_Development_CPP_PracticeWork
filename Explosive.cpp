// Fill out your copyright notice in the Description page of Project Settings.


#include "Explosive.h"
#include "MainCharacter.h"

AExplosive::AExplosive()
{
	damage = 30.f;
}


void AExplosive::onOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::onOverlapBegin(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	UE_LOG(LogTemp, Warning, TEXT("Explosive::OnOverlapBegin()"));

	if (OtherActor)
	{
		
		/** converting the @OtherActor into AMainCharacter, basically Casting.
		/* if cast fails then @main will contain null pointer... */
		AMainCharacter* main = Cast<AMainCharacter>(OtherActor);
		
		/** ...then This if will fail. */
		if (main)
		{
			/** accessing the @decrementHealth() -> from the maincharacter. */
			main->decrementHealth(damage);
		}
	}

}
void AExplosive::onOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::onOverlapEnd(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);

	UE_LOG(LogTemp, Warning, TEXT("Explosive::OnOverlapEnd()"));
}