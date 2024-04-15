// Fill out your copyright notice in the Description page of Project Settings.


#include "Pawns/Player/PlayerTankPawn.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/TankASC.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Game/TankPlayerState.h"
#include "GameFramework/SpringArmComponent.h"

APlayerTankPawn::APlayerTankPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(GetMesh());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APlayerTankPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitAbilityActorInfo();
	AddTankAbilities();
}

void APlayerTankPawn::InitAbilityActorInfo()
{
	ATankPlayerState* TankPlayerState = GetPlayerState<ATankPlayerState>();
	check(TankPlayerState);
	TankPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(TankPlayerState, this);
	Cast<UTankASC>(TankPlayerState->GetAbilitySystemComponent())->SetTankAbilityInfo();
	AbilitySystemComponent = TankPlayerState->GetAbilitySystemComponent();
	AttributeSet = TankPlayerState->GetAttributeSet();
	
	InitializeDefaultAttributes();
}

UTankASC* APlayerTankPawn::GetASC()
{
	/*
	 * Check to see if there is a valid ability system component on the character.
	 * If there is not get one.
	 * If so, return the existing ASC
	 */
	if (TankAbilitySystemComponent == nullptr)
	{
		TankAbilitySystemComponent = Cast<UTankASC>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(this));
	}
	return TankAbilitySystemComponent;
}

void APlayerTankPawn::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Initialize Ability Info on the client
	InitAbilityActorInfo();
}

void APlayerTankPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void APlayerTankPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
