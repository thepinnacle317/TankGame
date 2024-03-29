// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/TankVehicleAnimationInstance.h"
#include "Pawns/Player/PlayerTankPawn.h"

void UTankVehicleAnimationInstance::NativeInitializeAnimation()
{	
	// Get the pawn that owns this animation instance
	TankPawn = Cast<APlayerTankPawn>(TryGetPawnOwner());
	if (TankPawn == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Tank Pawn Cast Failed in Native Initialization"));
	}
}
