// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "WarMachine.h"
#include "Turret.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class ACannon;
class UArrowComponent;
class APawn;


UCLASS()
class TANKSMASH_API ATurret : public AWarMachine
{
	GENERATED_BODY()
	
protected:

	UPROPERTY()
		APawn* PlayerPawn;

	//settings
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargettingRange = 1000.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargettingSpeed = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float TargettingRate = 0.005f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
		float Accurency = 10;

	//link for meshes
	const FString BodyMeshPath { "StaticMesh'/Game/CSC/Meshes/SM_CSC_Tower1.SM_CSC_Tower1'" };
	const FString TurretMeshPath {"StaticMesh'/Game/CSC/Meshes/SM_CSC_Gun1.SM_CSC_Gun1'"};

public:	
	ATurret();
	
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	void Targetting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	bool IsPlayerSeen();
};
