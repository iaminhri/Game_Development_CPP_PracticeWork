// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingPlatform.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

// Sets default values
AFloatingPlatform::AFloatingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Floater"));
	RootComponent = mesh;
	
	startPoint = FVector(0.f);
	endPoint = FVector(0.f);

	bInterping = false;

	interpSpeed = 1.f;
	interpTime = 1.f;
}

// Called when the game starts or when spawned
void AFloatingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	startPoint = GetActorLocation();

	/** @endPoint is relative local to world startPoint position */
	endPoint += startPoint;

	bInterping = false;

	GetWorldTimerManager().SetTimer(fTimer, this, &AFloatingPlatform::toggleInterping, interpTime);

	// @size returns the magnitude of the vector
	distance = (endPoint - startPoint).Size();
}

// Called every frame
void AFloatingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bInterping)
	{
		//Gets actor current location
		FVector currentLocation = GetActorLocation();

		/** @interp takes a VInterpTo function which interpolates in between two points (startPoint and endPoint) */
		FVector interp = FMath::VInterpTo(currentLocation, endPoint, DeltaTime, interpSpeed);
		SetActorLocation(interp);

		float distanceTraveled = (GetActorLocation() - startPoint).Size();
		if (distance - distanceTraveled <= 1.f)
		{
			toggleInterping();
			
			GetWorldTimerManager().SetTimer(fTimer, this, &AFloatingPlatform::toggleInterping, interpTime);

			swapVectors(startPoint, endPoint);
		}
	}
}

void AFloatingPlatform::toggleInterping()
{
	bInterping = !bInterping;
}

void AFloatingPlatform::swapVectors(FVector& vecOne, FVector& vecTwo)
{
	FVector temp;
	temp = vecOne;
	vecOne = vecTwo;
	vecTwo = temp;
}
