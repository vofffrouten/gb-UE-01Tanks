// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "Turret.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class ACannon;
class UArrowComponent;
class APawn;

UCLASS()
class TANKSMASH_API ATurret : public AActor, public IDamageTaker
{
	GENERATED_BODY()
	
protected:
	//body
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;

	//cannon
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetupPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
		TSubclassOf<ACannon> CannonClass;
	UPROPERTY()
		ACannon* Cannon;

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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;

public:	
	ATurret();
	UFUNCTION()
		void TakeDamage(FDamageData DamageData);
	
protected:
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	void Targetting();
	void RotateToPlayer();
	bool IsPlayerInRange();
	bool CanFire();
	void Fire();
	
	UFUNCTION()
		void Die();
	UFUNCTION()
		void DamageTaked(float DamageValue);
};
