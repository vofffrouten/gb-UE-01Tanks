// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameStructs.h"
#include "CoreMinimal.h"
#include "Cannon.h"
#include "GameFramework/Actor.h"
#include "DamageTaker.h"
#include "WarMachine.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UHealthComponent;

UCLASS()
class TANKSMASH_API AWarMachine : public APawn, public IDamageTaker
{
	GENERATED_BODY()

public:
	UFUNCTION()
		void TakeDamage(FDamageData DamageData);

	UFUNCTION()
		void Fire();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;
	UPROPERTY()
		ACannon* Cannon;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetupPoint;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Cannon")
		TSubclassOf<ACannon> CannonClass;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;
//	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components|Effects")
//		class UAudioComponent* AudioEffectDie;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UAudioComponent* AudioEffectIncome;

	UFUNCTION()
		void Die();
	UFUNCTION()
		void DamageTaked(float DamageValue);
};
