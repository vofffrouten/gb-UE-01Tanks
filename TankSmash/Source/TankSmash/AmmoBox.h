// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameStructs.h"
#include "Cannon.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoBox.generated.h"

class UBoxComponent;

UCLASS()
class TANKSMASH_API AAmmoBox : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* BoxCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		EBoxType Type = EBoxType::Ammo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		int AAmmoCount {10};

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
		TSubclassOf<ACannon> CannonClass;

public:	
	AAmmoBox();

protected:
	UFUNCTION()
	void OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
