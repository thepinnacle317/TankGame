// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AbilitySystemInterface.h"
#include "WheeledVehiclePawn.h"
#include "Interfaces/TankInterface.h"
#include "TankPawnBase.generated.h"


/* Forward Declarations */
struct FInputActionValue;
class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;
class UCapsuleComponent;
class UChaosWheeledVehicleMovementComponent;


UCLASS()
class TANKGAME_API ATankPawnBase : public AWheeledVehiclePawn , public IAbilitySystemInterface, public ITankInterface
{
	GENERATED_BODY()

public:
	ATankPawnBase();
	virtual void Tick(float DeltaTime) override;

	/* Ability System */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	TObjectPtr<UChaosWheeledVehicleMovementComponent> VehicleMovementComponent;

	/* Death */
	UFUNCTION(NetMulticast, Reliable)
	virtual void MulticastTankDeath();
	virtual void Death() override;

	/* Tank Properties */
	
	/* Tank Lights */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float LightIntensity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EmissiveIntensity;

protected:
	virtual void BeginPlay() override;
	bool bDead = false;

	/* Ability System */
	void ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffectClass, float Level) const;
	virtual void InitializeDefaultAttributes() const;
	virtual void InitAbilityActorInfo();
	void AddTankAbilities();
	virtual AActor* GetAvatar_Implementation() override;
	

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Tank Properties|Gameplay Effects")
	TSubclassOf<UGameplayEffect> DefaultTankAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Tank Properties|Gameplay Effects")
	TSubclassOf<UGameplayEffect> SecondaryTankAttributes;

private:
	UPROPERTY(EditAnywhere, Category="Tank Properties|Startup Abilities")
	TArray<TSubclassOf<UGameplayAbility>> TankStartupAbilities;
};
