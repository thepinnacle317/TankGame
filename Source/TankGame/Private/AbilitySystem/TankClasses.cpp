// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/TankClasses.h"

FTankClassAbilityDetails UTankClasses::GetTankClassDefaultInfo(ETankClasses TankClasses)
{
	// Performs an assertion and checks for the information.
	return TankClassInformation.FindChecked(TankClasses);
}
