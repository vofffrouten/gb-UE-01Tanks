
#pragma once

#include "CoreMinimal.h"
#include "TankPawn.h"
#include "GameFramework/Actor.h"
#include "TankFactory.generated.h"

class ATargetPoint;

UCLASS()
class TANKSMASH_API ATankFactory : public AActor, public IDamageTaker
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BuildingMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BuildingMeshDestroyed;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UArrowComponent* TankSpawnPoint;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UBoxComponent* HitCollider;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UHealthComponent* HealthComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Tank Params")
		TSubclassOf<ATankPawn> SpawnTankClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Tank Params")
		float SpawnTankRate = 3.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn Tank Params")
		TArray<ATargetPoint*> TankWayPoint;

	bool isDead{ false };

public:	
	ATankFactory();
	UFUNCTION()
		void TakeDamage(FDamageData DamageData);

protected:
	virtual void BeginPlay() override;
	void SpawnNewTank();

	UFUNCTION()
		void Die();

	UFUNCTION()
		void DamageTaked(float DamageValue);
};
