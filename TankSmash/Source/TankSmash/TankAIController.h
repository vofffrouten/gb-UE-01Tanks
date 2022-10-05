// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATankPawn;

UCLASS()
class TANKSMASH_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	UPROPERTY()
		ATankPawn* TankPawn;
	UPROPERTY()
		APawn* PlayerPawn;


	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "AI|Move params|Patrol points", Meta = (MakeEditWidget = true))
		TArray <FVector> PatrollingPoints;
	int32 PatrollingIndex{ 0 };

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "AI|Move params|Accurency")
		float MovementAccurency;	

	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Targeting")
		float TargetingRange = 1000.0f;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Targeting")
		float TargetingSpeed = 0.1f;
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "Targeting")
		float TargetingAccurancy = 10.0f;

public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	float GetRotationValue();
	void Targeting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();
	
	bool IsPlayerSeen();
};

