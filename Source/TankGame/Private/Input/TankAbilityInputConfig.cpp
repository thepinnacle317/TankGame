// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/TankAbilityInputConfig.h"

const UInputAction* UTankAbilityInputConfig::GetAbilityInputByTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	// Finds the tag that is assigned to the Input Action
	for (const FTankInputs& InputAction : TankAbilityInputs)
	{
		if (InputAction.InputAction && InputAction.InputTag == InputTag)
		{
			return InputAction.InputAction;
		}
	}

	// Error message for Tank Abilities that have not been linked to the called InputTag
	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find AbilityInputAction for InputTag [%s], on InputConfig [%s]"), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}
