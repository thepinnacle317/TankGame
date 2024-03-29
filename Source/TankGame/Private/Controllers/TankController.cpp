// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/TankController.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "ChaosVehicleMovementComponent.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameplayTagContainer.h"
#include "InputActionValue.h"
#include "AbilitySystem/TankASC.h"
#include "Input/TankEnhancedInputComponent.h"
#include "Pawns/TankPawnBase.h"

ATankController::ATankController()
{
	bReplicates = true;
}

void ATankController::BeginPlay()
{
	Super::BeginPlay();

	// Halts Execution if the TankIMC has not been assigned
	check(TankContext);
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (Subsystem) Subsystem->AddMappingContext(TankContext, 0);
}

void ATankController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	// Pointer to the Controlled Pawn.
	TankPawn = CastChecked<ATankPawnBase>(InPawn);
}

void ATankController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set the Enhanced Input Component
	UTankEnhancedInputComponent* TankEnhancedInputComponent = CastChecked<UTankEnhancedInputComponent>(InputComponent);
	/* Throttle */
	TankEnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Triggered, this, &ThisClass::Throttle);
	TankEnhancedInputComponent->BindAction(ThrottleAction, ETriggerEvent::Completed, this, &ThisClass::Throttle);

	/* Steering */
	TankEnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Triggered, this, &ThisClass::Steering);
	TankEnhancedInputComponent->BindAction(SteeringAction, ETriggerEvent::Completed, this, &ThisClass::Steering);

	/* Braking */
	TankEnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Triggered, this, &ThisClass::Brake);
	TankEnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Started, this, &ThisClass::StartBrake);
	TankEnhancedInputComponent->BindAction(BrakeAction, ETriggerEvent::Completed, this, &ThisClass::StopBrake);

	/* Turret */
	TankEnhancedInputComponent->BindAction(TurretLookAction, ETriggerEvent::Triggered, this, &ThisClass::TurretLook);
	TankEnhancedInputComponent->BindAction(TurretLookAction, ETriggerEvent::Completed, this, &ThisClass::TurretLook);

	/* Ability Inputs */
	TankEnhancedInputComponent->BindAbilityInputs(TankAbilityInputs, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased);
}

void ATankController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (GetTankASC())
	{
		GetTankASC()->AbilityInputTagPressed(InputTag);
		GEngine->AddOnScreenDebugMessage(-6, 3.f, FColor::Blue, FString("Pressed"));
	}
}

void ATankController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (GetTankASC())
	{
		GetTankASC()->AbilityInputTagReleased(InputTag);
		GEngine->AddOnScreenDebugMessage(-6, 3.f, FColor::Blue, FString("Released"));
	}
}

void ATankController::Throttle(const FInputActionValue& InputActionValue)
{
	// Get the Input Magnitude for the throttle
	ThrottleValue = InputActionValue.Get<float>();
	if (TankPawn)
	{
		TankPawn->VehicleMovementComponent->SetThrottleInput(ThrottleValue);
		GEngine->AddOnScreenDebugMessage(2, 3.f, FColor::Orange, FString::Printf(TEXT("Throttle Value: %f"), ThrottleValue));
	}
}

void ATankController::Steering(const FInputActionValue& InputActionValue)
{
	SteeringValue = InputActionValue.Get<float>();

	if (TankPawn)
	{
		// Reverse the input value when going backwards
		bReversing ? SteeringValue *= -1 : SteeringValue *= 1;
	
		if (bReversing == false)
		{
			// Adds a small throttle input to help steer faster when turning in place.  Helps counteract the physics force
			if (ThrottleValue < .2f && SteeringValue != 0.f)
			{
				TankPawn->VehicleMovementComponent->SetThrottleInput(.1f);
			}
		}
		
		TankPawn->VehicleMovementComponent->SetYawInput(SteeringValue);
		GEngine->AddOnScreenDebugMessage(3, 3.f, FColor::Orange, FString::Printf(TEXT("Steering Value: %f"), SteeringValue));
	}
}

void ATankController::TurretLook(const FInputActionValue& InputActionValue)
{
	const FVector2d LookAxisVector = InputActionValue.Get<FVector2d>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
	}
}

void ATankController::Brake(const FInputActionValue& InputActionValue)
{
	BrakeValue = InputActionValue.Get<float>();

	if (TankPawn)
	{
		TankPawn->VehicleMovementComponent->SetBrakeInput(BrakeValue);
		BrakeValue > 0.f ? bReversing = true : bReversing = false;
		GEngine->AddOnScreenDebugMessage(4, 3.f, FColor::Orange, FString::Printf(TEXT("Brake Value: %f"), BrakeValue));
	}
}

void ATankController::StartBrake(const FInputActionValue& InputActionValue)
{
	// Handle lights or anything else braking involved here
}

void ATankController::StopBrake(const FInputActionValue& InputActionValue)
{
	// Handle lights or anything else braking involved here
	if (TankPawn)
	{
		TankPawn->VehicleMovementComponent->SetBrakeInput(0.0f);
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
	GEngine->AddOnScreenDebugMessage(5, 3.f, FColor::Orange, FString::Printf(TEXT("Reversing?: %s"), bReversing ? TEXT("True") : TEXT("False")));
}
