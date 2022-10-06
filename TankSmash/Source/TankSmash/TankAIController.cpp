// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAIController.h"
#include "TankPawn.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	TankPawn = Cast<ATankPawn>(GetPawn());
	PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	FVector pawnLocation = TankPawn->GetActorLocation();
	MovementAccurency = TankPawn->GetMovementAccurancy();
	TArray <FVector> points = TankPawn->GetPatrollingPoints();

	for (FVector point : points) {
		PatrollingPoints.Add(point + pawnLocation);
	//	UE_LOG(LogTemp, Warning, TEXT("The vector value is: %s"), *point.ToString());
	}

	PatrollingIndex = 0;

}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TankPawn->MoveForward(0.5);

	float rotationValue = GetRotationValue();
	TankPawn->RotateRight(rotationValue);

	Targeting();
}


float ATankAIController::GetRotationValue()
{
	FVector currentPoint = PatrollingPoints[PatrollingIndex];
	FVector pawnLocation = TankPawn->GetActorLocation();
	//UE_LOG(LogTemp, Warning, TEXT("Current point is: %s    Loc: %s"), *currentPoint.ToString(), *pawnLocation.ToString());

	float distance = FVector::Distance(currentPoint, pawnLocation);

	if (distance <= MovementAccurency) {
		PatrollingIndex++;
		if (PatrollingIndex >= PatrollingPoints.Num()) {
			PatrollingIndex = 0;
		}
	}

	FVector moveDirection = currentPoint - pawnLocation;
	moveDirection.Normalize();
	FVector forwardDirection = TankPawn->GetActorForwardVector();
	FVector rightDirection = TankPawn->GetActorRightVector();

	//DrawDebugLine(GetWorld(), pawnLocation, currentPoint, FColor::Blue, false, 0.5, 0, 6);

	float forwardAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(forwardDirection, moveDirection)));
	float rightAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(rightDirection, moveDirection)));

	float rotationValue = 0;
	if (forwardAngle > 5) {
		rotationValue = 1;
	}
	if (rightAngle > 90) {
		rotationValue = -rotationValue;
	}
	return rotationValue;
}

void ATankAIController::Targeting()
{
	if (CanFire())
		Fire();
	else
		RotateToPlayer();
}

void ATankAIController::RotateToPlayer()
{
	if (IsPlayerInRange())
		TankPawn->RotateTurretTo(PlayerPawn->GetActorLocation());
}

bool ATankAIController::IsPlayerInRange()
{
	return FVector::Distance(TankPawn->GetActorLocation(), PlayerPawn->GetActorLocation()) <= TargetingRange;
}

bool ATankAIController::CanFire()
{
	if (!IsPlayerSeen())
		return false;

	FVector targetingDirect = TankPawn->GetForwardTurretVector();
	FVector directToPlayer = PlayerPawn->GetActorLocation() - TankPawn->GetActorLocation();
	directToPlayer.Normalize();
	float aimAngle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(targetingDirect, directToPlayer)));
	return aimAngle <= TargetingAccurancy;
}

void ATankAIController::Fire()
{
	return TankPawn->Fire();
}

bool ATankAIController::IsPlayerSeen()
{
	FVector playerPos = PlayerPawn->GetActorLocation();
	FVector eyesPos = TankPawn->GetEyesPosition();

	FHitResult hitResult;
	FCollisionQueryParams traceParams =	FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.AddIgnoredActor(TankPawn);
	traceParams.bReturnPhysicalMaterial = false;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, eyesPos, playerPos, ECollisionChannel::ECC_GameTraceChannel1, traceParams)) {
		if (hitResult.GetActor()) {
			DrawDebugLine(GetWorld(), eyesPos, hitResult.Location, FColor::Red, false, 0.5f, 0, 10);
			//UE_LOG(LogTemp, Warning, TEXT("Collided with %s. "), *hitResult.GetActor()->GetName());
			return hitResult.GetActor() == PlayerPawn;
		}
	}

	DrawDebugLine(GetWorld(), eyesPos, playerPos, FColor::Orange, false, 0.5f, 0, 10);
	return false;
}



