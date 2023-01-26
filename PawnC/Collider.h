// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Collider.generated.h"

UCLASS()
class PRAC1_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider();

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* meshComponent;
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USphereComponent* sphereComponent;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UCameraComponent* Camera;
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USpringArmComponent* springArm;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UColliderMovementComponent* ourMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	FORCEINLINE void setMeshComponent(UStaticMeshComponent* mesh) { meshComponent = mesh; }
	FORCEINLINE UStaticMeshComponent* getMeshComponent() { return meshComponent; }
	FORCEINLINE void setSphereComponent(USphereComponent* sphere) { sphereComponent = sphere; }
	FORCEINLINE USphereComponent* getSphereComponent() { return sphereComponent; }

	FORCEINLINE void setCameraComponent(UCameraComponent* inCamera) { Camera = inCamera; }
	FORCEINLINE UCameraComponent* getCameraComponent() { return Camera; }
	FORCEINLINE void setSpringArmComponent(USpringArmComponent* inSpringArm) { springArm = inSpringArm; }
	FORCEINLINE USpringArmComponent* getSpringArmComponent() { return springArm; }

private:
	void moveForward(float value);
	void moveRight(float value);
	void pitchCamera(float axisVal);
	void yawCamera(float axisVal);

	FVector2D cameraInput;

};