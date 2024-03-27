// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TankGameplayAbility.h"
#include "Pawns/TankPawnBase.h"
#include "Controllers/TankController.h"

void UTankGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

ATankController* UTankGameplayAbility::GetTankControllerFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<ATankController>(CurrentActorInfo->PlayerController.Get()) : nullptr);
}

ATankPawnBase* UTankGameplayAbility::GetTankPawnFromActorInfo() const
{
	return (CurrentActorInfo ? Cast<ATankPawnBase>(CurrentActorInfo->AvatarActor.Get()) : nullptr);
}
