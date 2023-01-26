// Fill out your copyright notice in the Description page of Project Settings.


#include "Item.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Volume"));
	RootComponent = collisionVolume;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->SetupAttachment(GetRootComponent());

	idleParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("IdleParticleSystemComponent"));
	idleParticleComponent->SetupAttachment(GetRootComponent());

	bRotate = false;
	rotationRate = 45.f;

}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();

	collisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AItem::onOverlapBegin);
	collisionVolume->OnComponentEndOverlap.AddDynamic(this, &AItem::onOverlapEnd);
	
}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotate)
	{
		FRotator rotation = GetActorRotation();

		/** rotates the actor */
		rotation.Yaw += DeltaTime * rotationRate;

		SetActorRotation(rotation);
	}

}

void AItem::onOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin()"));

	if (overlapParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), overlapParticles, GetActorLocation(), FRotator(0.f), true);
	}

	if (overlapSound)
	{
		UGameplayStatics::PlaySound2D(this, overlapSound);
	}
	//Destroy the actor and everything else inside of the actor, UPROPERTY() helps garbage collection.
	Destroy();

}
void AItem::onOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("OnOverlapEnd()"));
}