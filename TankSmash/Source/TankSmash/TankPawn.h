// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cannon.h"
#include "CoreMinimal.h"
#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"
#include "DamageTaker.h"
#include "WarMachine.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;
class UHealthComponent;

UCLASS()
class TANKSMASH_API ATankPawn : public AWarMachine
{
	GENERATED_BODY()

protected:	

	// speed of moving and rotating
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float MoveSpeed { 100.0f };
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float RotateSpeed { 100.0f };

	// camera
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components|Camera")
		UCameraComponent* Camera;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components|Camera")
		USpringArmComponent* SpringArm;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float InterpolationKey{ 0.1f };

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
		float turretInterpolationKey;

	float ForwardMoveAxisValue { 0.0f };
	float RightMoveAxisValue { 0.0f };
	
	float RightRotateAxisValue { 0.0f };
	float CurrentRotateAxisValue{ 0.0f };

	UPROPERTY()
		ATankPlayerController* TankController;
		//cannon

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
		TSubclassOf<ACannon> SecondCannonClass;

	//for AI
	UPROPERTY(EditAnywhere, BluePrintReadWrite, Category = "AI|Move params|Patrol Points", Meta = (MakeEditWidget = true))
		TArray <FVector> PatrollingPoints;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI|Move params|Accurancy")
		float MovementAccurency = 5.0f;

public:	

	ATankPawn();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);

	UFUNCTION()
	void RotateRight(float Value);
	
	UFUNCTION()
	void ChangeCannon();

	UFUNCTION()
	void SpecialFire();

	UFUNCTION()
	void SetupCannon();

	UFUNCTION()
	void AddCannonAmmo(int ammo);

	UFUNCTION()
	void NewCannon(TSubclassOf<ACannon> newCannon);
		
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	//for AI
	UFUNCTION()
		TArray<FVector> GetPatrollingPoints() { return PatrollingPoints; };
	UFUNCTION()
		float GetMovementAccurancy() { return MovementAccurency; };

	UFUNCTION()
		FVector GetForwardTurretVector();
	
	UFUNCTION()
		void RotateTurretTo(FVector TargetPos);

	UFUNCTION()
		FVector GetEyesPosition();

protected:
	virtual void BeginPlay() override;

};
