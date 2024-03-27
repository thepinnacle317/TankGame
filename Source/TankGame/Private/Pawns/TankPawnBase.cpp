// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TankPawnBase.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystem/TankASC.h>

ATankPawnBase::ATankPawnBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATankPawnBase::MulticastTankDeath_Implementation()
{
	// Deal with tank collision and physics here.

	bDead = true;
}

void ATankPawnBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATankPawnBase::ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const
{
	// Make sure there is a valid ASC and GameplayEffectClass assigned
	check(IsValid(GetAbilitySystemComponent()));
	check(GameplayEffectClass);

	// Wraps the FGameplayEffectContext to allow for replication
	FGameplayEffectContextHandle EffectContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	// Sets the object the effect was created from
	EffectContextHandle.AddSourceObject(this);
	// Allows blueprints to generate a GameplayEffectSpec once and then reference it by handle, to apply it multiple times/multiple targets
	const FGameplayEffectSpecHandle EffectSpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffectClass, Level, EffectContextHandle);

	/*
	 * Applies the GameplayEffect to the target and uses the SourceObject which is this class.  This will allow us to apply effects to all classes that inherit from this.
	 * This also gives the option to set prediction on the client in the future.
	 */
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*EffectSpecHandle.Data.Get(), GetAbilitySystemComponent());
}

void ATankPawnBase::InitializeDefaultAttributes() const
{
	ApplyEffectToSelf(DefaultTankAttributes, 1.f);
}

void ATankPawnBase::InitAbilityActorInfo()
{
}

void ATankPawnBase::AddTankAbilities()
{
	UTankASC* TankASC = CastChecked<UTankASC>(AbilitySystemComponent);

	// Check if the server has authority since this will be a server call
	if (!HasAuthority()) return;
	TankASC->AddTankAbilities(TankStartupAbilities);
}

void ATankPawnBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UAbilitySystemComponent* ATankPawnBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

