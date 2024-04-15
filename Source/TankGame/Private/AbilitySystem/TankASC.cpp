// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TankASC.h"
#include <AbilitySystem/Abilities/TankGameplayAbility.h>

UTankASC::UTankASC()
{
}

void UTankASC::SetTankAbilityInfo()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UTankASC::ClientEffectApplied);
}

void UTankASC::AddTankAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : StartupAbilities)
	{
		// Adds the Startup Tag for the Ability linked to the Input.  This can be changed at runtime.
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		if (const UTankGameplayAbility* TFAbility = Cast<UTankGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(TFAbility->InputTag);
			GiveAbility(AbilitySpec);
		}
	}
}

void UTankASC::AbilityInputTagPressed(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	/* Check if we have an ability that can be activated that is paired to the Input Tag and
	 * try to activate it if there is a matching Tag to the Input.
	 */
	for (FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
	{
		if (AbilitySpec.Ability && (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)))
		{
			if (AbilitySpec.IsActive())
			{
				// Ability is active so pass along the input event
				AbilitySpecInputPressed(AbilitySpec);
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputPressed, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
			}
			else
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UTankASC::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;
	/* Check if we have an ability that can be activated that is paired to the Input Tag and
	 * try to activate it if there is a matching Tag to the Input.
	 */
	for (FGameplayAbilitySpec& AbilitySpec : ActivatableAbilities.Items)
	{
		if (AbilitySpec.Ability && (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)))
		{
			if (AbilitySpec.IsActive())
			{
				// Ability is active so pass along the input event
				AbilitySpecInputReleased(AbilitySpec);
				UE_LOG(LogTemp, Warning, TEXT("AbilitySpecInputReleased: %s"), *InputTag.ToString());
				InvokeReplicatedEvent(EAbilityGenericReplicatedEvent::InputReleased, AbilitySpec.Handle, AbilitySpec.ActivationInfo.GetActivationPredictionKey());
			}
		}
	}
}

void UTankASC::ClientEffectApplied_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);
	EffectAssetTags.Broadcast(TagContainer);
}
