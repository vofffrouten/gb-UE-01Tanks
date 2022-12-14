// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "TankPlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "WarMachine.h"
#include "Components/ArrowComponent.h"

ATankPawn::ATankPawn()
{
 	PrimaryActorTick.bCanEverTick = true;
	
	// create gizmo for Body Mesh and Turret Mesh
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Body"));
	RootComponent = BodyMesh;

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Tank collision box"));
	// create hierarchy of objects
	HitCollider->SetupAttachment(BodyMesh);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Tank Turret"));
	TurretMesh->SetupAttachment(BodyMesh);

	//create Cannon
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

	// create camera Spring
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring arm"));
	SpringArm->SetupAttachment(HitCollider);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	// create camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);	

	//health
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &ATankPawn::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATankPawn::DamageTaked);

	//audio
//	AudioEffectDie = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Die"));
//	AudioEffectDie->SetupAttachment(BodyMesh);
//	AudioEffectDie->SetAutoActivate(false);

	AudioEffectIncome = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Income"));
	AudioEffectIncome->SetupAttachment(BodyMesh);
	AudioEffectIncome->SetAutoActivate(false);
}


FVector ATankPawn::GetForwardTurretVector()
{
	return TurretMesh->GetForwardVector();
}

void ATankPawn::RotateTurretTo(FVector TargetPos)
{
	FRotator currentTurRotation = TurretMesh->GetComponentRotation();
	FRotator targetTurRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetPos);

	//exclude X Y
	targetTurRotation.Pitch = currentTurRotation.Pitch;
	targetTurRotation.Roll = currentTurRotation.Roll;

	TurretMesh->SetWorldRotation(FMath::Lerp(targetTurRotation, currentTurRotation, turretInterpolationKey));
}

FVector ATankPawn::GetEyesPosition()
{
	return CannonSetupPoint->GetComponentLocation();
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	//take controller
	TankController = Cast<ATankPlayerController>(GetController());

	SetupCannon();
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
		RotateTurretTo(mousePos);
	}
}

//cannonsetups
void ATankPawn::SetupCannon()
{
	if (Cannon) {
		Cannon->Destroy();
	}

	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

//Chenge Cannon on Click
void ATankPawn::ChangeCannon()
{
	Swap(CannonClass, SecondCannonClass);
	SetupCannon();
}

//Get Cannon from Crate
void ATankPawn::NewCannon(TSubclassOf<ACannon> newCannon)
{
	if (!newCannon) {
		return;
	}
	CannonClass = newCannon;
	SetupCannon();
}


void ATankPawn::SpecialFire()
{
	if (Cannon) {
		Cannon->SpecialFire();
	}
}

void ATankPawn::AddCannonAmmo(int ammo)
{
	Cannon->AddAmmo(ammo);
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}


