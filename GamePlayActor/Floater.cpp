// Fill out your copyright notice in the Description page of Project Settings.


#include "Floater.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
//Constructor
AFloater::AFloater()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));

	initialLoc = FVector(0.0f);
	placedLoc = FVector(0.0f);
	worldOrigin = FVector(0.0f, 0.0f, 0.0f);
	initialDirection = FVector(0.0f, 0.0f, 0.0f);

	bShouldFloat = false;
	bInitializeFloaterLocations = false;

	initialForce = FVector(2000000.f, 0.0f, 0.0f);
	initialTorque = FVector(2000000.f, 0.0f, 0.0f);

	runningTime = 0.f;
	A = 0.f;
	B = 0.f;
	C = 0.f;
	D = 0.f;

}

// Called when the game starts or when spawned
//BeginPlayFunction
void AFloater::BeginPlay()
{
	Super::BeginPlay();

	//FMath::FRand() -> randomizes value between 0-1
	//FMath::FRandRange() -> Randomizes Value Between two points (any point number 0 - 100 or 200 - 300 or -500, 500)
	float initialX = FMath::FRandRange(-500.f, 500.f);
	float initialY = FMath::FRandRange(-500.f, 500.f);
	float initialZ = FMath::FRandRange(0.0f, 500.f);

	initialLoc.X = initialX;
	initialLoc.Y = initialY;
	initialLoc.Z = initialZ;

	//initialLoc *= 200;

	placedLoc = GetActorLocation();

	if (bInitializeFloaterLocations)
	{
		SetActorLocation(initialLoc);
	}

	baseZLocation = placedLoc.Z;
	
	//FHitResult hitResult;
	//FRotator rotation = FRotator(0.0f, 0.0f, 30.0f);
	//Rotates Around World Axes
	//AddActorWorldOffset(localOffset, true, &hitResult);
	//AddActorLocalRotation(rotation);

	//StaticMesh->AddForce(intialForce);
	//StaticMesh->AddTorque(intialTorque);
	
}

// Called every frame
void AFloater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FHitResult hitResult;

	if (bShouldFloat)
	{
		FVector newLocation = GetActorLocation();

		newLocation.Z = baseZLocation + A * FMath::Sin(B * runningTime - C) + D;

		SetActorLocation(newLocation);
		runningTime += DeltaTime;
		
		/*AddActorLocalOffset(initialDirection, true, &hitResult);
		FVector hitLocation = hitResult.Location;
		UE_LOG(LogTemp, Warning, TEXT("Hit Location: x = %f, y = %f, z = %f"), hitLocation.X, hitLocation.Y, hitLocation.Z);
		*/
	}

	//InPitch = y, InYaw = z, InRoll = x;
	//FRotator rotation = FRotator(0.0f, 1.0f, 0.0f);
	//Rotate Around Local Axes.
	//AddActorLocalRoation(rotation);
	//Rotates Around World Axes, if tempered with local axes it still moves around the world axes.
	//AddActorWorldRotation(rotation);

}

