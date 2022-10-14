
#include "TankFactory.h"
#include "TimerManager.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "DamageTaker.h"
#include "HealthComponent.h"

ATankFactory::ATankFactory()
{
	PrimaryActorTick.bCanEverTick = false;
	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComp;

	BuildingMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Mesh"));
	BuildingMesh->SetupAttachment(sceneComp);

	BuildingMeshDestroyed = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Building Mesh Destroyed"));
	BuildingMeshDestroyed->SetupAttachment(sceneComp);
	BuildingMeshDestroyed->SetVisibility(false);

	TankSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Tank Spawn Point"));
	TankSpawnPoint->SetupAttachment(BuildingMesh);

	HitCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("HitCollider"));
	HitCollider->SetupAttachment(sceneComp);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health component"));
	HealthComponent->OnDie.AddUObject(this, &ATankFactory::Die);
	HealthComponent->OnDamaged.AddUObject(this, &ATankFactory::DamageTaked);	
}

void ATankFactory::BeginPlay()
{

}

void ATankFactory::TakeDamage(FDamageData DamageData)
{

}

void ATankFactory::Die()
{

}

void ATankFactory::DamageTaked(float DamageValue)
{

}

void ATankFactory::SpawnNewTank()
{

}

