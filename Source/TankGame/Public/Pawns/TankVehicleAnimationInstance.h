// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "VehicleAnimationInstance.h"
#include "TankVehicleAnimationInstance.generated.h"


/* Forward Declarations */
class APlayerTankPawn;
class UChaosVehicleMovementComponent;


/**
 * 
 */
UCLASS()
class TANKGAME_API UTankVehicleAnimationInstance : public UVehicleAnimationInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;

	UPROPERTY(BlueprintReadOnly, Category="Tank Properties")
    TObjectPtr<APlayerTankPawn> TankPawn;

};
