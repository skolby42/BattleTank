// Copyright Scott Kolby 2020

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"

// Depends on movement component via pathfinding system

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	auto ControlledTank = GetPawn();
	if (!ensure(PlayerTank && ControlledTank))
		return;

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	auto TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
		TankAimingComponent->Fire();
}