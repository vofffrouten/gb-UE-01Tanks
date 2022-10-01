// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameStructs.h"
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IScorable.generated.h"

UINTERFACE(MinimalAPI)
class UIScorable : public UInterface
{
	GENERATED_BODY()
};

class TANKSMASH_API IIScorable
{
	GENERATED_BODY()

public:
	virtual void GetScores(FScores Scores) = 0;
};
