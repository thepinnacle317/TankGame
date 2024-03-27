// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pawns/TankPawnBase.h"
#include "PlayerTankPawn.generated.h"


class UTankASC;
/* Forward Declarations */
class UCapsuleComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class USpringArmComponent;


/**
 * 
 */
UCLASS()
class TANKGAME_API APlayerTankPawn : public ATankPawnBase
{
	GENERATED_BODY()

public:
	APlayerTankPawn();

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
	virtual void PostInitializeComponents() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> DefaultRoot;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> Camera;

protected:

private:
	virtual void InitAbilityActorInfo() override;

	/* Ability System */
	UTankASC* GetASC();
	UPROPERTY()
	TObjectPtr<UTankASC> TankAbilitySystemComponent;
};
