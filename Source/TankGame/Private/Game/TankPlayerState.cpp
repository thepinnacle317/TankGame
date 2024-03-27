// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/TankPlayerState.h"

#include "AbilitySystem/TankASC.h"
#include "AbilitySystem/TankAttributeSet.h"
#include "Net/UnrealNetwork.h"

ATankPlayerState::ATankPlayerState()
{
	// Adds and Constructs the ASC to the Player State that will be handled on the server
	AbilitySystemComponent = CreateDefaultSubobject<UTankASC>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	
	// Only replicate minimal gameplay effect info to simulated proxies but full info to owners and autonomous proxies 
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	// Adds and Constructs the AS to the Player State that will be handled on the server
	AttributeSet = CreateDefaultSubobject<UTankAttributeSet>("Attribute Set");
	
	/*
	 * How often the server will try to update the clients.  Used for replication.  100 will serve as the baseline.
	 * This can be tweaked for performance
	 */
	NetUpdateFrequency = 100.f;
}

void ATankPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Add the Player Level to the Replicated Properties.  See Header for more useful functions to use.
	DOREPLIFETIME(ATankPlayerState, Level);
}

UAbilitySystemComponent* ATankPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATankPlayerState::OnRep_Level(int32 OldLevel)
{
	//TODO: Handle the player level and replication
}
