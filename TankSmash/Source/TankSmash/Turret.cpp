// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TankPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/ArrowComponent.h"
#include "Turret.h"
#include "Cannon.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "WarMachine.h"
#include "TimerManager.h"


ATurret::ATurret()
{
	//PrimaryActorTick.bCanEverTick = true;
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Body"));
	RootComponent = BodyMesh;
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Turret"));
	TurretMesh->AttachToComponent(BodyMesh,	FAttachmentTransformRules::KeepRelativeTransform);
	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setup point"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Hit Collider"));
	HitCollider->SetupAttachment(TurretMesh);

	//link geometry by path
	UStaticMesh* turretMeshMap = LoadObject<UStaticMesh>(this, *TurretMeshPath);
	if (turretMeshMap) {
		TurretMesh->SetStaticMesh(turretMeshMap);
	}
	UStaticMesh* bodyMeshMap = LoadObject<UStaticMesh>(this, *BodyMeshPath);
	if (bodyMeshMap) {
		BodyMesh->SetStaticMesh(bodyMeshMap);
	}

	//health
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &ATurret::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATurret::DamageTaked);

	AudioEffectIncome = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Income"));
	AudioEffectIncome->SetupAttachment(BodyMesh);
	AudioEffectIncome->SetAutoActivate(false);
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
	FActorSpawnParameters params;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);
	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FTimerHandle targetingTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(targetingTimerHandle, this, &ATurret::Targetting, TargettingRate, true, TargettingRate);

	Cannon->AddAmmo(30);
}

void ATurret::Destroyed()
{
	if (Cannon) {
		Cannon->Destroy();
	}
}

void ATurret::Targetting()
{	
	if (IsPlayerInRange()) {
		RotateToPlayer();
	}
	if (CanFire() && Cannon -> IsReadyToFire() && Cannon) {
		Fire();
	}
}

void ATurret::RotateToPlayer()
{
	FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), PlayerPawn->GetActorLocation());
	FRotator currentRotation = TurretMesh->GetComponentRotation();
	targetRotation.Pitch = currentRotation.Pitch;
	targetRotation.Roll = currentRotation.Roll;
	TurretMesh->SetWorldRotation(FMath::Lerp(currentRotation, targetRotation, TargettingSpeed));
}

bool ATurret::IsPlayerInRange()
{
	return FVector::Distance(PlayerPawn->GetActorLocation(), GetActorLocation()) <= TargettingRange;
}

bool ATurret::CanFire()
{
	if (!IsPlayerSeen()) {
		return false;
	}
	FVector targettingDir = TurretMesh->GetForwardVector();
	FVector dirToPlayer = PlayerPawn->GetActorLocation() - GetActorLocation();
	dirToPlayer.Normalize();

	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targettingDir, dirToPlayer)));

	return aimAngle <= Accurency;
}

bool ATurret::IsPlayerSeen()
{
	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = CannonSetupPoint->GetComponentLocation();

	FHitResult hitResult;
	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.AddIgnoredActor(this);
	traceParams.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECollisionChannel::ECC_Visibility, traceParams)) {
		if (hitResult.GetActor()) {
			DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Red, false, 0.5f, 0, 10);
			//UE_LOG(LogTemp, Warning, TEXT("Collided with %s. "), *hitResult.GetActor()->GetName());
			return hitResult.GetActor() == PlayerPawn;
		}
	}

	DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Orange, false, 0.5f, 0, 10);
	return false;
}




