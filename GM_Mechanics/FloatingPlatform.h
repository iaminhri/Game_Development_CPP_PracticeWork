// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingPlatform.generated.h"

UCLASS()
class PRAC1_API AFloatingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingPlatform();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Floater")
	class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "Floater")
	FVector startPoint;

	/** @meta = (MakeEditWidget) -> set to true enables in viewport endPoint XYZ axis */
	UPROPERTY(EditAnywhere, meta = (MakeEditWidget = "true"))
	FVector endPoint;

	UPROPERTY(EditAnywhere, Category = "Floater")
	float interpSpeed;

	UPROPERTY(EditAnywhere, Category = "Floater")
	float interpTime;

	UPROPERTY(EditAnywhere, Category = "Floater")
	FTimerHandle fTimer;

	UPROPERTY(EditAnywhere, Category = "Floater")
	bool bInterping;

	float distance;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void toggleInterping();
	void swapVectors(FVector& vecOne, FVector& vecTwo);

};
