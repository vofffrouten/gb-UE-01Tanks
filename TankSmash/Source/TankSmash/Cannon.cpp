// Fill out your copyright notice in the Description page of Project Settings.

#include "Cannon.h"
#include "GameStructs.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ACannon::ACannon()
{
 	PrimaryActorTick.bCanEverTick = false;

	//create object from nowhere
	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = sceneComp;

	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cannon mesh"));
	CannonMesh->SetupAttachment(sceneComp);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Spawn point"));
	ProjectileSpawnPoint->SetupAttachment(CannonMesh);
}

void ACannon::Fire()
{
	if (!ReadyToFire || AmmoCount <= 0) {
		return;
	}
	ReadyToFire = false;
	--AmmoCount;

	if (Type == ECannonType::FireProjectile) {
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Blue, "!!!PROJECTILE!!!");
	} else {
		GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "!!!TRACE!!!");
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);
}


void ACannon::SpecialActualFire()
{
	GEngine->AddOnScreenDebugMessage(10, 1, FColor::Blue, "!!!SPECIAL~~~BADA~~~~BOOOM!!!!");
}

void ACannon::SpecialFire()
{
	if (!SplReadyToFire || SplAmmoCount < SplFireAmmoAtOnce) {
		return;
	}
	SplReadyToFire = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::SplReload, 1 / SplFireRate, false);
	for (size_t i = 0; i < SplFireAmmoAtOnce; i++)
	{
		--SplAmmoCount;
		GetWorld()->GetTimerManager().SetTimer(SpecialFireTimerHandle, this, &ACannon::SpecialActualFire, 0.1f, false);
		UE_LOG(LogTemp, Warning, TEXT("SplAmmoCount = %d"), SplAmmoCount);
	}
}

bool ACannon::SplIsReadyToFire()
{
	return SplReadyToFire;
}


bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

void ACannon::Reload()
{
	ReadyToFire = true;
}

void ACannon::SplReload()
{
	SplReadyToFire = true;
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
	SplReload();
}



