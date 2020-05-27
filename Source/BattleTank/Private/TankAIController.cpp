// Copyright Scott Kolby 2020

#include "TankAIController.h"
#include "Engine/World.h"
#include "TankAimingComponent.h"
#include "Tank.h"

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
	if (!PlayerTank || !ControlledTank)
		return;

	// Move towards the player
	MoveToActor(PlayerTank, AcceptanceRadius);

	auto TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());

	if (TankAimingComponent->GetFiringState() == EFiringState::Locked)
		TankAimingComponent->Fire();
}

void ATankAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (!InPawn)
		return;

	auto ControlledTank = Cast<ATank>(InPawn);
	if (!ControlledTank)
		return;

	ControlledTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn())
		return;
	
	GetPawn()->DetachFromControllerPendingDestroy();
}
