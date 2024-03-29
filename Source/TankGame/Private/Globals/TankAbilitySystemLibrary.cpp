// Fill out your copyright notice in the Description page of Project Settings.


#include "Globals/TankAbilitySystemLibrary.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/TankClasses.h"
#include "Game/TankGameModeBase.h"
#include "Interfaces/TankInterface.h"
#include "Kismet/GameplayStatics.h"

void UTankAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ETankClasses TankClasses,
                                                            float level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();

	UTankClasses* TankClass = GetTankClassDetails(WorldContextObject);

	const FTankClassAbilityDetails TankDetails = TankClass->GetTankClassDefaultInfo(TankClasses);

	// Apply the GameplayEffects to the Defined Tank Classes

	/* Vital Attributes */
	FGameplayEffectContextHandle VitalEffectContextHandle = ASC->MakeEffectContext();
	VitalEffectContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalSpecHandle = ASC->MakeOutgoingSpec(TankDetails.VitalAttributes, level, VitalEffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalSpecHandle.Data.Get());

	/* Secondary Attributes */
	FGameplayEffectContextHandle SecondaryEffectContextHandle = ASC->MakeEffectContext();
	SecondaryEffectContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondarySpecHandle = ASC->MakeOutgoingSpec(TankDetails.SecondaryAttributes, level, SecondaryEffectContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondarySpecHandle.Data.Get());
}

void UTankAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ETankClasses TankClasses)
{
	ATankGameModeBase* TankGameMode = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (TankGameMode == nullptr) return;

	/* Tank Common Abilities */
	UTankClasses* TankClass = TankGameMode->TankClasses;
	for (TSubclassOf<UGameplayAbility> Abilities : TankClass->TankCommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Abilities, 1);
		ASC->GiveAbility(AbilitySpec);
	}

	/* Startup Abilities */
	const FTankClassAbilityDetails TankDefaults = TankClass->GetTankClassDefaultInfo(TankClasses);
	for (TSubclassOf<UGameplayAbility> Abilities : TankDefaults.StartingAbilities)
	{
		ITankInterface* TankInterface = Cast<ITankInterface>(ASC->GetAvatarActor());
		if (TankInterface)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Abilities, TankInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);
		}
	}
}

UTankClasses* UTankAbilitySystemLibrary::GetTankClassDetails(const UObject* WorldContextObject)
{
	ATankGameModeBase* TankGameMode = Cast<ATankGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (TankGameMode == nullptr) return nullptr;
	return TankGameMode->TankClasses;
}