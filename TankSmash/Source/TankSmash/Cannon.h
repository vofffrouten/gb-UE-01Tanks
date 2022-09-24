// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "Components/SplineMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Projectile.h"
#include "Cannon.generated.h"

class UArrowComponent;

UCLASS()
class TANKSMASH_API ACannon : public AActor
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* CannonMesh;

	//startShooting point
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRate = 1;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float FireDamage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		ECannonType Type = ECannonType::FireProjectile;

	FTimerHandle ReloadTimerHandle;
	bool ReadyToFire = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		int AmmoCount = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		int SplAmmoCount = 6;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		float SplFireRate = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		int SplFireAmmoAtOnce = 3;

	FTimerHandle SpecialTimerHandle;
	FTimerHandle SpecialFireTimerHandle;
	bool SplReadyToFire = false;

	//Projectile
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire params")
		TSubclassOf<AProjectile> ProjectileClass;

public:	
	ACannon();
	
	void Fire();
	bool IsReadyToFire();
	void ProjectileFire();
	void TraceFire();
	
	void SpecialFire();
	bool SplIsReadyToFire();
	void SpecialActualFire();

protected:
	virtual void BeginPlay() override;
	void Reload();
	void SplReload();
};
