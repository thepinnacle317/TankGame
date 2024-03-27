// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "TankPawnBase.generated.h"

/* Forward Declarations */
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

UCLASS()
class TANKGAME_API ATankPawnBase : public APawn , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATankPawnBase();
	virtual void Tick(float DeltaTime) override;

	/* Ability System */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

	TObjectPtr<USkeletalMesh> TankMesh;

	/* Death */
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastTankDeath();

protected:
	virtual void BeginPlay() override;

	bool bDead = false;

	/* Ability System */
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	virtual void InitializeDefaultAttributes() const;
	void AddTankAbilities();

	TObjectPtr<UAttributeSet> AttributeSet;

	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Tank Properties|Gameplay Effects")
	TSubclassOf<UGameplayEffect> DefaultTankAttributes;

private:
	TArray<TSubclassOf<UGameplayAbility>> TankStartupAbilities;
};
