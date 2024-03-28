// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TankAbilityInputConfig.generated.h"


/* Forward Declarations */
struct FGameplayTag;
class UInputAction;

// Used to link the Input Action to the InputTag
USTRUCT(BlueprintType)
struct FTankInputs
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();
};


/**
 * 
 */
UCLASS()
class TANKGAME_API UTankAbilityInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	// Used to locate the InputTag assigned to an ability and linked to the InputAction
	const UInputAction* GetAbilityInputByTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;

	// Stores an Array of the Tanks Ability Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FTankInputs> TankAbilityInputs;
};
