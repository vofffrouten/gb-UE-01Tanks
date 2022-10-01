// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cannon.h"
#include "CoreMinimal.h"
#include "TankPlayerController.h"
#include "GameFramework/Pawn.h"
#include "DamageTaker.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TANKSMASH_API ATankPawn : public APawn, public IDamageTaker
{
	GENERATED_BODY()

public:
	
	ATankPawn();

protected:
	
	virtual void BeginPlay() override;
	// box for tanks Body mesh
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	// box for tanks Turret mesh
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;
	// box of collisions
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BoxCollision;

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
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetupPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
		TSubclassOf<ACannon> CannonClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
		TSubclassOf<ACannon> SecondCannonClass;
	
	UPROPERTY()
		ACannon* Cannon;

public:	
	
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
	void Fire();

	UFUNCTION()
	void SpecialFire();

	UFUNCTION()
	void SetupCannon();

	UFUNCTION()
	void AddCannonAmmo(int ammo);

	UFUNCTION()
	void NewCannon(TSubclassOf<ACannon> newCannon);
		
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void TakeDamage(FDamageData DamageData);
};
