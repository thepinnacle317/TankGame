// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Controllers/TankController.h"
#include "Pawns/TankPawnBase.h"
#include "TankGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class TANKGAME_API UTankGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, Category = "Ability Properties|Ability Input")
	FGameplayTag InputTag;

	ATankController* GetTankControllerFromActorInfo() const;

	ATankPawnBase* GetTankPawnFromActorInfo() const;
	
};
