// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TankAbilities/TankFireAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actors/Projectiles/TankProjectile.h"
#include "Globals/TankGameplayTags.h"

void UTankFireAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                       const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                       const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UTankFireAbility::SpawnProjectile(const FVector& ProjectileTargetLocation)
{
	// Check to make sure that the actor is being called from the server or in single player.
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if(!bIsServer) return;

	// Get the socket location through the interface for the tank
	const FVector SocketLocation = ITankInterface::Execute_GetTankSocketLocation(GetAvatarActorFromActorInfo(), MainGunSocket);
	
	// Get the rotation from the target location to the socket
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();

	// Set the location and rotation for where to spawn the projectile from
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	// Spawn the tank projectile
	ATankProjectile* TankProjectile = GetWorld()->SpawnActorDeferred<ATankProjectile>(
		TankProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	/*
	 * Get the SpecHandle through the ASC to pass into the DamageEffectSpecHandle.
	 * This is a lightweight method for sending data on the projectile.
	 */
	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	// Contexts may not be tracked by GC.
	FGameplayEffectContextHandle EffectContextHandle = SourceASC->MakeEffectContext();
	EffectContextHandle.SetAbility(this);
	EffectContextHandle.AddSourceObject(TankProjectile);
	FHitResult HitResult;
	HitResult.Location = ProjectileTargetLocation;
	EffectContextHandle.AddHitResult(HitResult);
	
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
	const FTankGameplayTags GameplayTags = FTankGameplayTags::Get();

	for (auto& Pair : DamageTypes)
	{
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, Pair.Key, ScaledDamage);
	}
	
	TankProjectile->DamageEffectSpecHandle = SpecHandle;
	TankProjectile->FinishSpawning(SpawnTransform);
}

