// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/World.h"
#include "Prac1/PawnC/Critter.h"

// Sets default values
ASpawnVolume::ASpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	spawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn"));

}

// Called when the game starts or when spawned
void ASpawnVolume::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/** RandomPointInBoundingBox takes input origin and extent of the box and randomizes a point and returns that random point */

FVector ASpawnVolume::getSpawnPoint()
{
	FVector Extent = spawnBox->GetScaledBoxExtent();
	FVector Origin = spawnBox->GetComponentLocation();

	FVector Point = UKismetMathLibrary::RandomPointInBoundingBox(Origin, Extent);

	return Point;
}


/** @UCLass is a generic class type where you can input any class type thus there are no boundaries and it takes any class that derives from UClass
* @Location is for the pawn class to spawn.
* @spawnActor<ACritter>() takes a class type to spawn, location, FRorator and spawn parameters.
*/

void ASpawnVolume::spawnOurPawn_Implementation(UClass* toSpawn, const FVector& location)
{
	if (toSpawn)
	{
		UWorld* world = GetWorld();

		FActorSpawnParameters spawnParams;

		if (world)
		{
			ACritter* critterSpawned = world->SpawnActor<ACritter>(toSpawn, location, FRotator(0.f), spawnParams);
		}
	}
}
