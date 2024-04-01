// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "TankProjectile.generated.h"


/* Forward Declarations */
class UNiagaraSystem;
class USphereComponent;
class UProjectileMovementComponent;


UCLASS()
class TANKGAME_API ATankProjectile : public AActor
{
	GENERATED_BODY()
	
public:	

	ATankProjectile();

	UPROPERTY(BlueprintReadWrite, meta = (ExposeOnSpawn = true))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, Replicated)
	TArray<AActor*> ActorsToIgnore;

protected:
	
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:

	// Lifespan of the projectile
	float LifeSpan;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> ProjectileSphere;

	UPROPERTY(EditAnywhere, Category = "Projectile Properties | Sound")
	TObjectPtr<USoundBase> ImpactSound;

	UPROPERTY(EditAnywhere, Category = "Projectile Properties | Sound")
	TObjectPtr<USoundBase> ProjectileSound;

	// Used so the sound is properly spawned and destroyed
	UPROPERTY()
	TObjectPtr<UAudioComponent> ProjectileSoundComponent;

	UPROPERTY(EditAnywhere, Category = "Projectile Properties | Effects")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	bool bDidHit = false;

};
