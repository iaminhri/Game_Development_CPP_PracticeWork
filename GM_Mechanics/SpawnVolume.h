// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class PRAC1_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawn")
	class UBoxComponent* spawnBox;

	//
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spawn")
	TSubclassOf<class ACritter> pawnToSpawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Spawn")
	FVector getSpawnPoint();

	/** @BlueprintNativeEvent Creates an event of the function in the blueprint, 
	*	@BlueprintCallable makes the function to call in the Blueprint
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Spawn")
	void spawnOurPawn(UClass* toSpawn, const FVector& location);
};
