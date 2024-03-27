// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "TankPlayerState.generated.h"

/* Forward Declarations */
class UAttributeSet;
class UAbilitySystemComponent;


/**
 * 
 */
UCLASS()
class TANKGAME_API ATankPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATankPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/* Ability System */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;


protected:
	/* Ability System */
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
	

private:

	/*
	 * Handles the player's level replication.
	 * It is managed in the player state since this is not destroyed on player death
	 * and will make handling respawning and initializing the player easier.
	 */
	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Level)
	int32 Level = 1;
	
	UFUNCTION()
	void OnRep_Level(int32 OldLevel);


public:
	// Getters
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	FORCEINLINE int32 GetPlayerLevel() const { return Level; }
	
	
};
