#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DamageTaker.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TANKSMASH_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

	//MY EVENTS
	DECLARE_EVENT(UHealthComponent, FOnDie)
	DECLARE_EVENT_OneParam(UHealthComponent, FOnHealthChanged, float)
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health values")
		float MaxHealth = 12;
	
	UPROPERTY()
		float CurrentHealth;

public:	
	UHealthComponent();
	
	//events
	FOnDie OnDie;
	FOnHealthChanged OnDamaged;
	
	void TakeDamage(FDamageData DamageData);
	float GetHealth() const;
	float GetHealthState() const;
	void AddHealth(float AddiditionalHealthValue);

};
