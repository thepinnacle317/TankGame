// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectiles/TankProjectile.h"


ATankProjectile::ATankProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ATankProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

