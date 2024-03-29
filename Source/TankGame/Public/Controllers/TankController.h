// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"


/* Forward Declarations */
class UChaosVehicleMovementComponent;
class ATankPawnBase;
class UTankAbilityInputConfig;
struct FInputActionValue;
class UTankASC;
struct FGameplayTag;
class UInputAction;
class UInputMappingContext;


/**
 * 
 */
UCLASS()
class TANKGAME_API ATankController : public APlayerController
{
	GENERATED_BODY()
public:
	ATankController();
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

	UPROPERTY(BlueprintReadOnly)
	bool bReversing;

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;

	TObjectPtr<ATankPawnBase> TankPawn;

private:
	/* Enhanced Input */
	
	UPROPERTY(EditAnywhere, Category = "Input System")
	TObjectPtr<UInputMappingContext> TankContext;
	UPROPERTY(EditAnywhere, Category = "Input System")
	TObjectPtr<UInputAction> ThrottleAction;
	UPROPERTY(EditAnywhere, Category = "Input System")
	TObjectPtr<UInputAction> SteeringAction;
	UPROPERTY(EditAnywhere, Category = "Input System")
	TObjectPtr<UInputAction> TurretLookAction;
	UPROPERTY(EditAnywhere, Category = "Input System")
	TObjectPtr<UInputAction> BrakeAction;
	

	/* Abilities */
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);

	/* Tank Ability Inputs */
	UPROPERTY(EditDefaultsOnly, Category = "Tank Ability Inputs")
	TObjectPtr<UTankAbilityInputConfig> TankAbilityInputs;

	/* Movement */
	void Throttle(const FInputActionValue& InputActionValue);
	void Steering(const FInputActionValue& InputActionValue);
	void TurretLook(const FInputActionValue& InputActionValue);
	void Brake(const FInputActionValue& InputActionValue);
	void StartBrake(const FInputActionValue& InputActionValue);
	void StopBrake(const FInputActionValue& InputActionValue);
	
	UPROPERTY(VisibleAnywhere)
	float SteeringValue;
	UPROPERTY(VisibleAnywhere)
	float ThrottleValue;
	UPROPERTY(VisibleAnywhere)
	float BrakeValue;
	UPROPERTY(VisibleAnywhere)
	FRotator TurretRotation;
	UPROPERTY(VisibleAnywhere)
	float BarrelInclination;

	/* Ability System */
	UTankASC* GetTankASC();
	UPROPERTY()
	TObjectPtr<UTankASC> TankASC;

};
