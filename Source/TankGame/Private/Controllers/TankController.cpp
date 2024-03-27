// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TankController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "AbilitySystem/TankASC.h"

ATankController::ATankController()
{
	bReplicates = true;
}

void ATankController::BeginPlay()
{
	Super::BeginPlay();
	check(TankContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem) Subsystem->AddMappingContext(TankContext, 0);
}

void ATankController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (GetTankASC())
	{
		GetTankASC()->AbilityInputTagPressed(InputTag);
		GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Blue, FString("Pressed"));
	}
}

void ATankController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetTankASC())
	{
		GetTankASC()->AbilityInputTagReleased(InputTag);
		GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Blue, FString("Released"));
	}
}

void ATankController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (GetTankASC())
	{
		GetTankASC()->AbilityInputTagHeld(InputTag);
		GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Blue, FString("Held"));
	}
}

void ATankController::MoveTriggered(const FInputActionValue& InputActionValue)
{
	const FVector2d InputAxisVector = InputActionValue.Get<FVector2d>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	// Gets the forward Vector & Right Vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void ATankController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2d LookAxisVector = InputActionValue.Get<FVector2d>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
	}
}

UTankASC* ATankController::GetTankASC()
{
	/*
	 * Check to see if there is a valid ability system component on the Tank.
	 * If there is not get one.
	 * If so, return the existing ASC
	 */
	if (TankASC == nullptr)
	{
		TankASC = Cast<UTankASC>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return TankASC;
}

void ATankController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
}

void ATankController::SetupInputComponent()
{
	Super::SetupInputComponent();
}


