// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"


/**
 * * * * * * * * Tank Gameplay Tags * * * * * * * * * *
 *
 * This is a Singleton containing the native Gameplay Tags
 *
 * This will be the first place you will begin the boilerplate process to adding
 * a new attribute to this framework.
 * 
 */

struct FTankGameplayTags
{
public:
 /*
  * This is a getter function to get the Gameplay Tags.  This is used since it does not require an instance of this
  * class in order to retrieve the tags that we need to access.
  */
 static const FTankGameplayTags& Get() { return GameplayTags; }

 // Used to create the Native Gameplay Tags.
 static void InitializeNativeGameplayTags();

 /* Attributes */
 FGameplayTag Attributes_Vitals_Health;
 FGameplayTag Attributes_Vitals_Armor;

 /* Secondary */
 FGameplayTag Attributes_Secondary_MaxHealth;
 FGameplayTag Attributes_Secondary_MaxArmor;

 /* Ability Tags */
 FGameplayTag Input_FireMain;
 FGameplayTag Input_FireSecondary;

 /* Damage tag */
 FGameplayTag Damage;

private:
 static FTankGameplayTags GameplayTags;
};