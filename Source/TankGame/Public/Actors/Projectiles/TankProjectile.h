// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankProjectile.generated.h"

UCLASS()
class TANKGAME_API ATankProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	ATankProjectile();
	virtual void Tick(float DeltaTime) override;

protected:
	
	virtual void BeginPlay() override;
	
	

};
