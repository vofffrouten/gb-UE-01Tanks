// Fill out your copyright notice in the Description page of Project Settings.


#include "WarMachine.h"
#include "GameStructs.h"
#include "DamageTaker.h"
#include "HealthComponent.h"
#include "Particles/ParticleSystemComponent.h"

void AWarMachine::TakeDamage(FDamageData DamageData)
{
	HealthComponent->TakeDamage(DamageData);
}

void AWarMachine::DamageTaked(float DamageValue)
{
	UE_LOG(LogTemp, Warning, TEXT("Turret %s taked damage:%f Health:%f"), *GetName(), DamageValue, HealthComponent->GetHealth());
	AudioEffectIncome->Play();
}

void AWarMachine::Die()
{
//	AudioEffectDie->Play();
	Destroy();
}

void AWarMachine::Fire()
{
	if (Cannon) {
		Cannon->Fire();
	}
}
