// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"
/**
 * 
 */

class ATankPawn;

UCLASS()
class TANKSMASH_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		ATankPawn* TankPawn;
public:
	virtual void SetPawn(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	
};
