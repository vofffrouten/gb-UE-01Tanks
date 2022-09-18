// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/PlayerController.h"
#include "TankPawn.h"
#include "TankPlayerController.h"

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
