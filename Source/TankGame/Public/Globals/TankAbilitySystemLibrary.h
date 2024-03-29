// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TankAbilitySystemLibrary.generated.h"


class UTankClasses;
/* Forward Declarations */
enum ETankClasses : uint8;
class UAbilitySystemComponent;


/**
 * 
 */
UCLASS()
class TANKGAME_API UTankAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, Category="TankAbilitySystemLibrary | Tank Details")
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, ETankClasses TankClasses, float level, UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable, Category="TankAbilitySystemLibrary | Tank Details")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ETankClasses EnemyClass);

	UFUNCTION(BlueprintCallable, Category="TankAbilitySystemLibrary | Tank Details")
	static UTankClasses* GetTankClassDetails(const UObject* WorldContextObject);

};
