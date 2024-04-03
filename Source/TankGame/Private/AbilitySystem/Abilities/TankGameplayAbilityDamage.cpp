// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/TankGameplayAbilityDamage.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

void UTankGameplayAbilityDamage::CauseDamage(AActor* TargetActor)
{
	FGameplayEffectSpecHandle DamageEffectSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, AbilityLevel);
	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes)
	{
		const float DamageMagnitude = Pair.Value.GetValueAtLevel(GetAbilityLevel());
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageEffectSpecHandle, Pair.Key, DamageMagnitude);
	}
	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageEffectSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}

bool UTankGameplayAbilityDamage::LineTrace(FHitResult& TraceHitResults)
{

	PlayerController = Cast<ATankController>(GetAvatarActorFromActorInfo()->GetInstigatorController());
	
	FCollisionQueryParams QueryParams;
	
	APawn* ControlledPawn = PlayerController->GetPawn();
	if(ControlledPawn)
	{
		QueryParams.AddIgnoredActor(ControlledPawn);
	}
	
	FVector LineTraceStartLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
	FVector ForwardDirection =PlayerController->PlayerCameraManager->GetActorForwardVector();
	FVector LineTraceEndLocation = LineTraceStartLocation + (ForwardDirection * TraceRange);
	DidHit = GetWorld()->LineTraceSingleByChannel(TraceHitResult, LineTraceStartLocation, LineTraceEndLocation, ECC_Visibility, QueryParams);
	if (DrawDebug == true)
	{
		DrawDebugLine(GetWorld(), LineTraceStartLocation, LineTraceEndLocation, FColor::Red, true, 2.0f);
	}

	if (TraceHitResult.bBlockingHit)
	{
		TraceHitLocation = TraceHitResult.ImpactPoint;
	}
	else
	{
		TraceHitLocation = TraceHitResult.TraceEnd;
	}

	
	return DidHit;
}
