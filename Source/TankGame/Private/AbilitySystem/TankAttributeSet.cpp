// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TankAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Globals/TankGameplayTags.h"
#include "Net/UnrealNetwork.h"

UTankAttributeSet::UTankAttributeSet()
{
	/* Map Key/Value pair for Tags to Attributes */
	const FTankGameplayTags& GameplayTags = FTankGameplayTags::Get();

	/* Attributes */
	TagToAttribute.Add(GameplayTags.Attributes_Vitals_Health, GetHealthAttribute);
	TagToAttribute.Add(GameplayTags.Attributes_Vitals_Armor, GetArmorAttribute);
	TagToAttribute.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagToAttribute.Add(GameplayTags.Attributes_Secondary_MaxArmor, GetMaxArmorAttribute);
}

void UTankAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	/* Attributes */
	DOREPLIFETIME_CONDITION_NOTIFY(UTankAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTankAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTankAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTankAttributeSet, MaxArmor, COND_None, REPNOTIFY_Always);
	
}

// Executes on an Attribute Preemptively.  *Not the best solution*
void UTankAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetArmorAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxArmor());
	}
}

// Executes on an Attribute once a Gameplay Effect has been called. ** Best Method **
void UTankAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Properties;
	SetEffectProperties(Data, Properties);

	// This will clamp the Attributes and applied from the startup effect specified in the tank pawn.
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
		UE_LOG(LogTemp, Error, TEXT("Changed Health on %s, Health: %f"), *Properties.TargetAvatarActor->GetName(), GetHealth());
	}
	if (Data.EvaluatedData.Attribute == GetArmorAttribute())
	{
		SetArmor(FMath::Clamp(GetArmor(), 0.f, GetMaxArmor()));
		UE_LOG(LogTemp, Error, TEXT("Changed Armor on %s, Armor: %f"), *Properties.TargetAvatarActor->GetName(), GetArmor());
	}

	// TODO: Handle Damage here
}

void UTankAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTankAttributeSet, Health, OldHealth);
}

void UTankAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTankAttributeSet, Armor, OldArmor);
}

void UTankAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTankAttributeSet, MaxHealth, OldMaxHealth);
}

void UTankAttributeSet::OnRep_MaxArmor(const FGameplayAttributeData& OldMaxArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTankAttributeSet, MaxArmor, OldMaxArmor);
}

// See Header file for any clarification on what is required for the ModCallbackData.
// It boils down to an EffectSpec, the Evaluated Data, and a Target.  It then computes this Data to be applied to the target.
void UTankAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data,
                                            FEffectProperties& Properties) const
{
	// Source = Causer of the Effect, Target = Target of the Effect (Owner of this AS)

	// Effect Context is Who/What is applied to the Pawn
	Properties.EffectContextHandle = Data.EffectSpec.GetContext();
	
	// Get the ASC of the original instigator who started the chain
	Properties.SourceASC = Properties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	// Check to make sure there is a valid ASC, AbilityActorInfo, and AvatarActor
	// Ability Actor Info holds cached data about the owning actor that will be need often for abilities to use.
	if (IsValid(Properties.SourceASC) && Properties.SourceASC->AbilityActorInfo.IsValid() && Properties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		// Get the Avatar Actor and Player Controller to set as the Source if we pass the check.
		Properties.SourceAvatarActor = Properties.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Properties.SourceController = Properties.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Properties.SourceController == nullptr && Properties.SourceAvatarActor != nullptr)
		{
			// Get the controller from the Source Avatar if one was not initially found
			if (const APawn* Pawn = Cast<APawn>(Properties.SourceAvatarActor))
			{
				Properties.SourceController = Pawn->GetController();
			}
		}
		if (Properties.SourceController)
		{
			// Get the Pawn from the Source Controller if one was not found
			Properties.SourcePawn = Cast<APawn>(Properties.SourceController->GetPawn());
		}
	}

	// Check that there is a valid Target Avatar Actor
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		// Set the Properties for the Target
		Properties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Properties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Properties.TargetPawn = Cast<APawn>(Properties.TargetAvatarActor);
		Properties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Properties.TargetAvatarActor);
	}
}
