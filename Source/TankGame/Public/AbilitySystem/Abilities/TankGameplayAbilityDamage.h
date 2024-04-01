// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TankGameplayAbility.h"
#include "TankGameplayAbilityDamage.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API UTankGameplayAbilityDamage : public UTankGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	void CauseDamage(AActor* TargetActor);

	UPROPERTY(EditAnywhere, Category = "Gameplay Ability | Properties")
	int32 AbilityLevel;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Gameplay Ability | Damage Effects")
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay Ability | Damage Types")
	TMap<FGameplayTag, FScalableFloat> DamageTypes;
};
