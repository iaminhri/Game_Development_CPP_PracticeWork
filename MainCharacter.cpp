// Fill out your copyright notice in the Description page of Project Settings.

#include "MainCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	cameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	cameraBoom->SetupAttachment(GetRootComponent());
	cameraBoom->TargetArmLength = 600.f;
	cameraBoom->bUsePawnControlRotation = true;

	GetCapsuleComponent()->SetCapsuleSize(40.f, 90.f);

	followCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	followCamera->SetupAttachment(cameraBoom, USpringArmComponent::SocketName);
	followCamera->bUsePawnControlRotation = false;

	/** Set our turn rates for input */
	baseTurnRate = 65.f;
	baseLookUpRate = 65.f;

	bUseControllerRotationYaw = false;
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 250.f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;


	maxHealth = 100.f;
	health = 65.f;
	maxStamina = 350.f;
	stamina = 120.f;
	coins = 0;

}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	/** bind axis calls every frame but bind action only works when pressed and released. */
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AMainCharacter::moveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AMainCharacter::moveRight);
	
	/** Yaw is for turn input and pitch is for lookup input */
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("TurnRate"), this, &AMainCharacter::turnAtRate);
	PlayerInputComponent->BindAxis(TEXT("LookUpAtRate"), this, &AMainCharacter::lookUpAtRate);
	
}

void AMainCharacter::moveForward(float axisValue)
{
	/**
	* @Controller is inherited from pawn, non-physical actors, possess a pawn to control it's action
	* using the controller to get the forward direction of the character
	*/

	if ( Controller != nullptr && axisValue != 0.f)
	{
		/** Control Rotation determines the viewing/aiming direction of the controlled pawn and affected by the player input
		* Find out the forward direction
		*/
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, rotation.Yaw, 0.f);

		/** Rotation matrix is information about x,y,z in particular rotation in space  */
		const FVector direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(direction, axisValue);
	}
}


void AMainCharacter::moveRight(float axisValue)
{
	/**
	* @Controller is inherited from pawn, non-physical actors, possess a pawn to control it's action
	* using the controller to get the forward direction of the character
	*/

	if (Controller != nullptr && axisValue != 0.f)
	{
		/** Control Rotation determines the viewing/aiming direction of the controlled pawn and affected by the player input
		* Find out the forward direction
		*/
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, rotation.Yaw, 0.f);

		/** Rotation matrix is information about x,y,z in particular rotation in space  */
		const FVector direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(direction, axisValue);
	}
}

void AMainCharacter::turnAtRate(float rate)
{
	/** AddControllerYawInput-> rotates the controller based on yaw input */
	AddControllerYawInput(rate * baseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::lookUpAtRate(float rate)
{
	AddControllerPitchInput(rate * baseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AMainCharacter::decrementHealth(float amount)
{
	if (health - amount <= 0.f)
	{
		health -= amount;
		die();
	}
	else
	{
		health -= amount;
	}
}

void AMainCharacter::incrementCoinCount(int32 amount)
{
	coins += amount;
}

void AMainCharacter::die()
{

}