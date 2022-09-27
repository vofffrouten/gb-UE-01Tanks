// Fill out your copyright notice in the Description page of Project Settings.

#include "GameStructs.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "TankPawn.h"
#include "AmmoBox.h"

AAmmoBox::AAmmoBox()
{
	PrimaryActorTick.bCanEverTick = false;

	USceneComponent* sceneComp = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = sceneComp;
	
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision Box"));
	BoxCollision->SetupAttachment(sceneComp);
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAmmoBox::OnMeshOverlapBegin);
	BoxCollision->SetCollisionProfileName(FName("OverlapAll"));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollision->SetGenerateOverlapEvents(true);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ammo Mesh"));
	Mesh->SetupAttachment(BoxCollision);
}

void AAmmoBox::OnMeshOverlapBegin(UPrimitiveComponent* OverlappedComp, 
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult& SweepResult)
{
	ATankPawn* TankPawn = Cast<ATankPawn>(OtherActor);
	if (TankPawn) {	
		if (Type == EBoxType::Cannon) {
			TankPawn->SetupCannon(CannonClass);
		} else {
			TankPawn->AddCannonAmmo(AAmmoCount);
		}
		Destroy();
	}
}


