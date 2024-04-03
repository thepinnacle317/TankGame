// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/TankGameplayAbilityDamage.h"
#include "TankFireAbility.generated.h"

class ATankProjectile;
/**
 * 
 */
UCLASS()
class TANKGAME_API UTankFireAbility : public UTankGameplayAbilityDamage
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Projectile Properties | Tank Projectile Class")
	TSubclassOf<ATankProjectile> TankProjectileClass;
	
	UFUNCTION(BlueprintCallable, Category = "Tank Game | Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);
	
};
