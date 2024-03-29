// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TankGameModeBase.generated.h"


/* Forward Declarations */
class UTankClasses;


/**
 * 
 */
UCLASS()
class TANKGAME_API ATankGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "Tank Class Data")
	TObjectPtr<UTankClasses> TankClasses;
};
