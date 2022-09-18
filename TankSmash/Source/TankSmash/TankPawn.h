// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class TANKSMASH_API ATankPawn : public APawn
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

	float ForwardMoveAxisValue;
	float RightMoveAxisValue;

public:	
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void MoveForward(float Value);

	UFUNCTION()
	void MoveRight(float Value);
		
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
