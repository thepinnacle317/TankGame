// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "TankAbilityInputConfig.h"
#include "TankEnhancedInputComponent.generated.h"


/* Forward Declarations */
struct FTankInputs;
class UTankAbilityInputConfig;


/**
 * 
 */
UCLASS()
class TANKGAME_API UTankEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename PressedInputType, typename ReleasedInputType>
	void BindAbilityInputs(const UTankAbilityInputConfig* InputConfig, UserClass* Object, PressedInputType PressedInput, ReleasedInputType ReleasedInput);
	
};

template <class UserClass, typename PressedInputType, typename ReleasedInputType>
void UTankEnhancedInputComponent::BindAbilityInputs(const UTankAbilityInputConfig* InputConfig, UserClass* Object,
	PressedInputType PressedInput, ReleasedInputType ReleasedInput)
{
	check(InputConfig)

	// Assigns the Input Action to the Input Tag
	for (const FTankInputs& TankInputs : InputConfig->TankAbilityInputs)
	{
		if (TankInputs.InputAction && TankInputs.InputTag.IsValid())
		{
			if (PressedInput)
			{
				BindAction(TankInputs.InputAction, ETriggerEvent::Started, Object, PressedInput, TankInputs.InputTag);
			}
			if (ReleasedInput)
			{
				BindAction(TankInputs.InputAction, ETriggerEvent::Completed, Object, ReleasedInput, TankInputs.InputTag);
			}
		}
	}
}
