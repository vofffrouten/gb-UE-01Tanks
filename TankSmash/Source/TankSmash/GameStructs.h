// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.generated.h"

//cannon type
UENUM(BlueprintType)
enum class ECannonType :uint8 {
	FireProjectile = 0 UMETA(Display = "Use Projectile"),
	FireTrace = 1 UMETA(Display = "Use Trace"),
	FireSpeed = 2 UMETA(DIsplay = "Use Speed Bullet")
};

//boxtypes
UENUM(BlueprintType)
enum class EBoxType :uint8 {
	Ammo = 0 UMETA(Display = "Ammo"),
	Cannon = 1 UMETA(Display = "Cannon")
};

USTRUCT()
struct FDamageData {
	GENERATED_BODY()

	UPROPERTY()
	float DamageValue;

	UPROPERTY()
	AActor* Instigator;

	UPROPERTY()
	AActor* DamageMaker;
};

USTRUCT()
struct FScores {
	GENERATED_BODY()

	UPROPERTY()
		int ScoresValue;

	UPROPERTY()
		AActor* DamageMaker;
};