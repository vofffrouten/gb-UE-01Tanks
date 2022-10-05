// Fill out your copyright notice in the Description page of Project Settings.

#include "Cannon.h"
#include "GameStructs.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "DamageTaker.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"
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

	ShootEffect = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ShootViz"));
	ShootEffect->SetupAttachment(ProjectileSpawnPoint);

	AudioEffect = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio shoot"));
}

void ACannon::ProjectileFire()
{
	--AmmoCount;
	//GEngine->AddOnScreenDebugMessage(10, 1, FColor::Blue, "!!!PROJECTILE!!!");
	AProjectile* projectile = GetWorld()->
		SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation());
	if (projectile) {
		projectile->Start();
	}
}

void ACannon::TraceFireDamage(AActor* OtherActor) 
{
	UE_LOG(LogTemp, Warning, TEXT("Laser %s collided with %s. "), *GetName(), *OtherActor->GetName());
	AActor* owner = GetOwner();
	AActor* ownerByOwner = (owner != nullptr) ? owner->GetOwner() : nullptr;

	if (OtherActor != owner && OtherActor != ownerByOwner) {
		IDamageTaker* damageTakerActor = Cast<IDamageTaker>(OtherActor);
		if (damageTakerActor) {
			FDamageData damageData;
			damageData.DamageValue = 1;
			damageData.Instigator = owner;
			damageData.DamageMaker = this;

			damageTakerActor->TakeDamage(damageData);
		}
		else {
			OtherActor->Destroy();
		}
	}
}

void ACannon::TraceFire()
{
	//GEngine->AddOnScreenDebugMessage(10, 1, FColor::Red, "!!!TRACE!!!");
	FHitResult hitResult;
	FCollisionQueryParams traceParams = FCollisionQueryParams(FName(TEXT("FireTrace")), true, this);
	traceParams.bTraceComplex = true;
	traceParams.bReturnPhysicalMaterial = false;
	--SplAmmoCount;

	FVector start = ProjectileSpawnPoint->GetComponentLocation();
	FVector end = ProjectileSpawnPoint->GetForwardVector() * FireRange + start;

	if (GetWorld()->LineTraceSingleByChannel(hitResult, start, end, ECollisionChannel::ECC_Visibility, traceParams)) {
		DrawDebugLine(GetWorld(), start, hitResult.Location, FColor::Red, false, 0.4f, 0, 4);
		if (hitResult.GetActor())
		{
			TraceFireDamage(hitResult.GetActor());
		}
	} else {
		DrawDebugLine(GetWorld(), start, end, FColor::Green, false, 0.4f, 0, 2);
	}
}

void ACannon::SpeedFire()
{
	--AmmoCount;
	//GEngine->AddOnScreenDebugMessage(10, 1, FColor::Blue, "!!!PROJECTILE!!!");
	AProjectile* projectile = GetWorld()->
		SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPoint->GetComponentLocation(),
			ProjectileSpawnPoint->GetComponentRotation());
	if (projectile) {
		projectile->SetMoveSpeed(2);
		projectile->Start();
	}
}

void ACannon::AddAmmo(int ammo)
{
	AmmoCount += ammo;
}

//made independent funcs for fire type (it was too hard to read)
void ACannon::Fire()
{
	if (!ReadyToFire || AmmoCount <= 0) {
		return;
	}
	ReadyToFire = false;

	if (Type == ECannonType::FireProjectile) {
		ProjectileFire();
	} else if (Type == ECannonType::FireTrace) {
		TraceFire();
	} else {
		SpeedFire();
	}
	GEngine->AddOnScreenDebugMessage(10, 1, FColor::Blue, FString::Printf(TEXT("Ammo left: %d"), AmmoCount));
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::Reload, 1 / FireRate, false);

	ShootEffect->ActivateSystem();
	AudioEffect->Play();
}

#pragma region specialFire

void ACannon::SpecialActualFire()
{
//	GEngine->AddOnScreenDebugMessage(10, 1, FColor::Blue, "!!!SPECIAL~~~BADA~~~~BOOOM!!!!");
}

void ACannon::SpecialFire()
{
	if (!SplReadyToFire || SplAmmoCount < SplFireAmmoAtOnce) {
		return;
	}
	SplReadyToFire = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &ACannon::SplReload, 1 / SplFireRate, false);
	--SplAmmoCount;

	for (size_t i = 0; i < SplFireAmmoAtOnce; i++)
	{
		GetWorld()->GetTimerManager().SetTimer(SpecialFireTimerHandle, this, &ACannon::SpecialActualFire, 0.1f, false);
		UE_LOG(LogTemp, Warning, TEXT("SplAmmoCount = %d"), SplAmmoCount);
	}
}

bool ACannon::SplIsReadyToFire()
{
	return SplReadyToFire;
}

void ACannon::SplReload()
{
	SplReadyToFire = true;
}

#pragma endregion specialFire

bool ACannon::IsReadyToFire()
{
	return ReadyToFire;
}

void ACannon::Reload()
{
	ReadyToFire = true;
}

void ACannon::BeginPlay()
{
	Super::BeginPlay();
	Reload();
	SplReload();
}



