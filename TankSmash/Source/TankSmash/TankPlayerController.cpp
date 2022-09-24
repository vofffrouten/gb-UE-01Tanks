// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "TankPawn.h"
#include "TankPlayerController.h"

ATankPlayerController::ATankPlayerController()
{
	//show mouse on screen
	bShowMouseCursor = true;
}

void ATankPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);
	TankPawn = Cast<ATankPawn>(GetPawn());
}

void ATankPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	// linking input with objects move
	InputComponent->BindAxis("MoveForward", this, &ATankPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATankPlayerController::MoveRight);
	InputComponent->BindAxis("RotateRight", this, &ATankPlayerController::RotateRight);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ATankPlayerController::Fire);
	InputComponent->BindAction("SpecialFire", IE_Pressed, this, &ATankPlayerController::SpecialFire);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	//check mouse position	
	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePos, mouseDirection);
	//check tank position
	FVector pawnPos = TankPawn->GetActorLocation();
	//set tankZ as mouseZ = 0 
	MousePos.Z = pawnPos.Z;
	//find the vector of direct "ray"
	FVector dir = MousePos - pawnPos;
	dir.Normalize();
	MousePos = pawnPos + dir * 1000;
	//Draw a line frm Tank to Mouse
	//DrawDebugLine(GetWorld(), pawnPos, MousePos, FColor::Blue, false, 0.1f, 0, 8);
}

void ATankPlayerController::MoveForward(float Value)
{
	if (TankPawn) {
		TankPawn->MoveForward(Value);
	}	
}

void ATankPlayerController::MoveRight(float Value)
{
	if (TankPawn) {
		TankPawn->MoveRight(Value);
	}
}

void ATankPlayerController::RotateRight(float Value)
{
	if (TankPawn) {
		TankPawn->RotateRight(Value);
	}
}

void ATankPlayerController::Fire()
{
	TankPawn->Fire();
}

void ATankPlayerController::SpecialFire()
{
	TankPawn->SpecialFire();
}
