// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TankGameAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API UTankGameAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	// Getter Function
	static UTankGameAssetManager& Get();

protected:
	//Engine Function Override
	virtual void StartInitialLoading() override;
	
};
