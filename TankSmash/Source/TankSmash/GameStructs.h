// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.generated.h"

//cannon type
UENUM(BlueprintType)
enum class ECannonType :uint8 {
	FireProjectile = 0 UMETA(Display = "Use Projectile"),
	FireTrace = 1 UMETA(Display = "Use Trace")	
};