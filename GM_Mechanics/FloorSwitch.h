// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class PRAC1_API AFloorSwitch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloorSwitch();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	class UBoxComponent* triggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	class UStaticMeshComponent* door;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	class UStaticMeshComponent* floor;

	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
	FVector initialDoorLocation;
	
	UPROPERTY(BlueprintReadWrite, Category = "Floor Switch")
	FVector initialFloorSwitchLocation;

	FTimerHandle switchHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor Switch")
	float switchTIme;

	bool bCharacterOnSwitch;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void onBeginOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void onEndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void raisingDoor();
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void loweringDoor();

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void raisingFloorSwitch();

	UFUNCTION(BlueprintImplementableEvent, Category = "Floor Switch")
	void loweringFloorSwitch();

	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
	void updateDoorLocation(float Z);

	UFUNCTION(BlueprintCallable, Category = "Floor Switch")
	void updateFloorSwitchLocation(float Z);

	void closeDoor();
};