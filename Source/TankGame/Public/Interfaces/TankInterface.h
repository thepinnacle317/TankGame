// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TankInterface.generated.h"


class ATankController;

UINTERFACE(MinimalAPI, BlueprintType)
class UTankInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TANKGAME_API ITankInterface
{
	GENERATED_BODY()
public:

	// Returns the Player's current level
	virtual int32 GetPlayerLevel();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool IsDead();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	AActor* GetAvatar();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	ATankController* GetTankController();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	FVector GetTankSocketLocation(const FName Socket);
	
	virtual void Death() = 0;
};
