// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorSwitch.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"

//constructor loads first
// Sets default values
AFloorSwitch::AFloorSwitch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	triggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	RootComponent = triggerBox;
	
	triggerBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	triggerBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	triggerBox->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	triggerBox->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);

	triggerBox->SetBoxExtent(FVector(62.f, 62.f, 32.f));


	floor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FloorSwitch"));
	floor->SetupAttachment(GetRootComponent());

	door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	door->SetupAttachment(GetRootComponent());

	switchTIme = 2.f;
	bCharacterOnSwitch = false;
}

// Called when the game starts or when spawned
void AFloorSwitch::BeginPlay()
{
	Super::BeginPlay();

	/**
	* AddDynamic binds a function to a delegate. For OnComponentBeginOverlap, we are binding a function to the Component's OnComponentBeginOverlap delegate.
	* This delegate can be thought of as a variable storing an object that can be associated with a function.
	* When an overlap event is triggered, the function will be called.
	*/

	triggerBox->OnComponentBeginOverlap.AddDynamic(this, &AFloorSwitch::onBeginOverLap);
	triggerBox->OnComponentEndOverlap.AddDynamic(this, &AFloorSwitch::onEndOverLap);

	initialDoorLocation = door->GetComponentLocation();
	initialFloorSwitchLocation = floor->GetComponentLocation();

}

// Called every frame
void AFloorSwitch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFloorSwitch::onBeginOverLap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OverLap Begin."));
	if (!bCharacterOnSwitch) bCharacterOnSwitch = true;
	raisingDoor();
	loweringFloorSwitch();
}

void AFloorSwitch::onEndOverLap( UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlap End."));
	if (bCharacterOnSwitch) bCharacterOnSwitch = false;
	GetWorldTimerManager().SetTimer(switchHandle, this, &AFloorSwitch::closeDoor, switchTIme);
}

void AFloorSwitch::updateDoorLocation(float Z)
{
	FVector newLocation = initialDoorLocation;
	newLocation.Z += Z;
	door->SetWorldLocation(newLocation);
}

void AFloorSwitch::updateFloorSwitchLocation(float Z)
{
	FVector newLocation = initialFloorSwitchLocation;
	newLocation.Z += Z;
	floor->SetWorldLocation(newLocation);
}

void AFloorSwitch::closeDoor()
{
	if (!bCharacterOnSwitch)
	{
		loweringDoor();
		raisingFloorSwitch();
	}
	
}