// Fill out your copyright notice in the Description page of Project Settings.


#include "Globals/TankGameAssetManager.h"
#include "Globals/TankGameplayTags.h"

/*
 * Singleton that is set in the Engine Config file under
 * [/Script/Engine.Engine]
 * AssetManagerClassName=/Script/TankGame.TankGameAssetManager
*/

UTankGameAssetManager& UTankGameAssetManager::Get()
{
	check(GEngine)

	// Store the Tank Game Asset Manager
	UTankGameAssetManager* TankGameAssetManager = Cast<UTankGameAssetManager>(GEngine->AssetManager);

	return *TankGameAssetManager;
}

void UTankGameAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	// Load the Native Gameplay Tags defined ing TankGameplayTags.h/.cpp
	FTankGameplayTags::InitializeNativeGameplayTags();
}
