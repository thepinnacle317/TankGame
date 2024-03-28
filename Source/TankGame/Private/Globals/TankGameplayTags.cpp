// Fill out your copyright notice in the Description page of Project Settings.


#include "Globals/TankGameplayTags.h"
#include "GameplayTagsManager.h"

FTankGameplayTags FTankGameplayTags::GameplayTags;

/*
 * The GameplayTagsManager is a Singleton as well in this framework.
 * It is responsible for holding a dictionary of the Tags that are in the game.
 */
void FTankGameplayTags::InitializeNativeGameplayTags()
{
	// The structure for the tags is by the Attribute type for the FName and then the description for the FString.

	/* Attributes */
	GameplayTags.Attributes_Vitals_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vitals.Health"), FString("Used to manage and effect the Health Attribute"));
	GameplayTags.Attributes_Vitals_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vitals.Armor"), FString("Used to manage and effect the Armor Attribute"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("Used to manage the Max Health Attribute"));
	GameplayTags.Attributes_Secondary_MaxArmor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxArmor"), FString("Used to the Max Armor Attribute"));

	/* Abilities */
	GameplayTags.Input_FireMain = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.FireMain"), FString("Used to fire the tanks main gun"));
	GameplayTags.Input_FireSecondary = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Input.FireSecondary"), FString("Used to fire the tanks secondary gun"));
	
	/* Damage */
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Used to apply damage"));
}


