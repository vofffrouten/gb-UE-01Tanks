// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "TankPlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"

ATankPawn::ATankPawn()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Tank collision box"));
	// create hierarchy of objects
	RootComponent = BodyMesh;

	// create gizmo for Body Mesh and Turret Mesh
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Body"));
	BodyMesh->SetupAttachment(BoxCollision);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	// create camera Spring
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(BoxCollision);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	// create camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}


void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	//take controller
	TankController = Cast<ATankPlayerController>(GetController());
}

void ATankPawn::MoveRight(float Value)
{
	RightMoveAxisValue = Value;
}

void ATankPawn::MoveForward(float Value)
{
	ForwardMoveAxisValue = Value;
}

void ATankPawn::RotateRight(float Value)
{
	RightRotateAxisValue = Value;
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//moving tank
	FVector currentLocation = GetActorLocation();
	FVector forwardVector = GetActorForwardVector();
	FVector rightVector = GetActorRightVector();
	FVector movePosition = currentLocation + forwardVector * MoveSpeed * ForwardMoveAxisValue * DeltaTime +
								rightVector * MoveSpeed * RightMoveAxisValue * DeltaTime;
	SetActorLocation(movePosition, true);

	//rotate tank
	CurrentRotateAxisValue = FMath::Lerp(CurrentRotateAxisValue, RightRotateAxisValue, InterpolationKey);
	
	FRotator currentRotation = GetActorRotation();
	float yawRotation = RotateSpeed * CurrentRotateAxisValue * DeltaTime;
	//only Z rotation
	yawRotation += currentRotation.Yaw;
	//build full Frotator with all coorPlanes
	FRotator newRotation (0, yawRotation, 0);
	SetActorRotation(newRotation);

	//rotate turret
	if (TankController) {
		FVector mousePos = TankController->GetMousePos();
		FRotator currentTurRotation = TurretMesh->GetComponentRotation();
		FRotator targetTurRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mousePos);
		
		//exclude X Y
		targetTurRotation.Pitch = currentTurRotation.Pitch;
		targetTurRotation.Roll = currentTurRotation.Roll;
		UE_LOG(LogTemp, Warning, TEXT("TurTarget Rotation = %s"), *targetTurRotation.ToString());

		TurretMesh->SetWorldRotation(FMath::Lerp(targetTurRotation, currentTurRotation, turretInterpolationKey));
	}
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

