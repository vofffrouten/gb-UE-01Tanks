// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Projectile.generated.h"

UCLASS()
class TANKSMASH_API AProjectile : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		USphereComponent* CollisionSphere;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		float MoveSpeed = 100;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		float MoveRate = 0.005f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
		float Damage = 1;

	FTimerHandle MoveTimer;

public:	
	AProjectile();

	void Start();

protected:
	UFUNCTION()
	void OnMeshOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, 
			class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, 
			const FHitResult& SweepResult);
	UFUNCTION()
		void Move();

};
