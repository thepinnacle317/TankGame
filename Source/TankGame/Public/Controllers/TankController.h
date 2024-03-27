// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankController.generated.h"

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

protected:
	virtual void BeginPlay() override;

private:
	/* Enhanced Input */
	
	UPROPERTY(EditAnywhere, Category = "Input System")
	TObjectPtr<UInputMappingContext> TankContext;
	UPROPERTY(EditAnywhere, Category = "Input System")
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, Category = "Input System")
	TObjectPtr<UInputAction> LookAction;

	/* Abilities */
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	/* Movement */
	void MoveTriggered(const FInputActionValue& InputActionValue);
	void Look(const FInputActionValue& InputActionValue);

	/* Ability System */
	UTankASC* GetTankASC();
	UPROPERTY()
	TObjectPtr<UTankASC> TankASC;
};
