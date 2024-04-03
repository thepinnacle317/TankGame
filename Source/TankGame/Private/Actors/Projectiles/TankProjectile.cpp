// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Projectiles/TankProjectile.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "GameplayEffect.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "TankGame/TankGame.h"


ATankProjectile::ATankProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ProjectileSphere = CreateDefaultSubobject<USphereComponent>("Projectile Sphere");
	SetRootComponent(ProjectileSphere);
	
	/* Collision Response */
	ProjectileSphere->SetCollisionObjectType(ECC_Projectile);
	ProjectileSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileSphere->SetCollisionResponseToChannels(ECR_Ignore);
	ProjectileSphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	ProjectileSphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	ProjectileSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	/* Projectile Movement */
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");

	// Default Projectile Properties *** TODO:in testing
	ProjectileMovementComponent->InitialSpeed = 6500.f;
	ProjectileMovementComponent->MaxSpeed = 10500.f;
	ProjectileMovementComponent->ProjectileGravityScale = .5f;
}

void ATankProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Set the projectiles lifespan
	SetLifeSpan(LifeSpan);

	ProjectileSphere->OnComponentBeginOverlap.AddDynamic(this, &ATankProjectile::OnSphereOverlap);

	ProjectileSoundComponent = UGameplayStatics::SpawnSoundAttached(ProjectileSound, GetRootComponent());
}

void ATankProjectile::Destroyed()
{
	// This is called if the server destroys the projectile before OnSphereOverlap is called on the client.
	// If this happens then the Server will still spawn the sound and particles.
	if (!bDidHit && !HasAuthority())
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactEffect, GetActorLocation());
		if (ProjectileSoundComponent)
		{
			ProjectileSoundComponent->Stop();
		}
		bDidHit = true;
	}
	if (ProjectileSoundComponent)
	{
		ProjectileSoundComponent->Stop();
	}
	Super::Destroyed();
}

void ATankProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!DamageEffectSpecHandle.Data.IsValid() || DamageEffectSpecHandle.Data.Get()->GetContext().GetEffectCauser() == OtherActor)
	{
		return;
	}

	if (!bDidHit)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactEffect, GetActorLocation());
	
		if (ProjectileSoundComponent)
		{
			ProjectileSoundComponent->Stop();
		}
		bDidHit = true;
	}
	if (HasAuthority())
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			// Apply the effect to the target.  You could also get the source and apply to target as an alternative method.
			// Both accomplish the same thing.         /* This returns the EffectSpec */
			TargetASC->ApplyGameplayEffectSpecToSelf(*DamageEffectSpecHandle.Data.Get());
		}

		Destroy();
	}
	else
	{
		bDidHit = true;
	}
}

void ATankProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ATankProjectile, ActorsToIgnore);
	
}

