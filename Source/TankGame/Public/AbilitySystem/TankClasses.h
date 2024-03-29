// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TankClasses.generated.h"


/* Forward Declarations */
class UGameplayAbility;
class UGameplayEffect;


// Declares the tank class types
UENUM(BlueprintType)
enum ETankClasses : uint8
{
	Abrams,
	Leopard,
	Merkava
};

// Used to assign the default info to each tank class
USTRUCT(BlueprintType)
struct FTankClassAbilityDetails
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category = "Tank Defaults | Attributes")
	TSubclassOf<UGameplayEffect> VitalAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tank Defaults | Attributes")
	TSubclassOf<UGameplayEffect> SecondaryAttributes;
	
	UPROPERTY(EditDefaultsOnly, Category = "Tank Defaults | Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;
};

/**
 * 
 */
UCLASS()
class TANKGAME_API UTankClasses : public UDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "Tank Class Info | Tank Class Map")
	TMap<ETankClasses, FTankClassAbilityDetails> TankClassInformation;

	UPROPERTY(EditDefaultsOnly, Category = "Tank Class Info | Common Abilities")
	TArray<TSubclassOf<UGameplayAbility>> TankCommonAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "Tank Class Info | Damage")
	TObjectPtr<UCurveTable> DamageCalCurveTable;

	FTankClassAbilityDetails GetTankClassDefaultInfo(ETankClasses TankClasses);
};
