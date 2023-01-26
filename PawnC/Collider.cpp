// Fill out your copyright notice in the Description page of Project Settings.


#include "Collider.h"
#include "Components/SphereComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "ColliderMovementComponent.h"

// Sets default values
ACollider::ACollider()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	sphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	//Making Sphere the Root Component
	SetRootComponent(sphereComponent);
	
	sphereComponent->InitSphereRadius(40.0f);
	sphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	meshComponent->SetupAttachment(GetRootComponent());
	

	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshComponentAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	if (meshComponentAsset.Succeeded())
	{
		meshComponent->SetStaticMesh(meshComponentAsset.Object);
		meshComponent->SetRelativeLocation(FVector(0.f, 0.f, -40.f));
		meshComponent->SetWorldScale3D(FVector(0.8f, 0.8f, 0.8f));
	}

	springArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	springArm->SetupAttachment(GetRootComponent());
	//springArm->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));
	springArm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));
	springArm->TargetArmLength = 400.f;
	springArm->bEnableCameraLag = true;
	springArm->CameraLagSpeed = 3.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Camera->SetupAttachment(springArm, USpringArmComponent::SocketName);
	//Camera->SetRelativeLocation(FVector(-300.f, 0.f, 0.f));
	//Camera->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	ourMovementComponent = CreateDefaultSubobject<UColliderMovementComponent>(TEXT("OurMovementComponent"));
	ourMovementComponent->UpdatedComponent = RootComponent;

	cameraInput = FVector2D(0.f, 0.f);

	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ACollider::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACollider::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator newRotation = GetActorRotation();	

	newRotation.Yaw += cameraInput.X;

	SetActorRotation(newRotation);
	
	FRotator NewSpringArmRotation = springArm->GetComponentRotation();

	NewSpringArmRotation.Pitch = FMath::Clamp( NewSpringArmRotation.Pitch += cameraInput.Y, -80.f, -15.f);

	springArm->SetWorldRotation(NewSpringArmRotation);
	
}

// Called to bind functionality to input
void ACollider::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACollider::moveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACollider::moveRight);
	PlayerInputComponent->BindAxis(TEXT("CameraPitch"), this, &ACollider::pitchCamera);
	PlayerInputComponent->BindAxis(TEXT("CameraYaw"), this, &ACollider::yawCamera);
	
}

void ACollider::pitchCamera(float axisVal)
{
	cameraInput.Y = axisVal;
}

void ACollider::yawCamera(float axisVal)
{
	cameraInput.X = axisVal;
}

// value var can only be 1 or -1 depends on the keyboard press
void ACollider::moveForward(float value)
{
	FVector forward = GetActorForwardVector();
	//AddMovementInput(value * forward);

	/*AddMovementInput function is inherited by pawn class
	the definition of the function is below
	*/
	if (ourMovementComponent)
	{
		ourMovementComponent->AddInputVector( forward * value );
	}
}

void ACollider::moveRight(float value)
{
	FVector right = GetActorRightVector();
	//AddMovementInput(value * right);

	if (ourMovementComponent)
	{
		ourMovementComponent->AddInputVector( right * value );
	}
}

UPawnMovementComponent* ACollider::GetMovementComponent() const
{
	return ourMovementComponent;
	/* returns in the form of UPawnMovementComponent, 
	as ColliderMovementComponent is derived from UPawnMovementComponent
	and ourMovementComponent is a property of ColliderMovementComponent
	*/
}
