// Copyright Scott Kolby 2020

#include "TankAIController.h"
#include "Tank.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	if (!PlayerTank || !ControlledTank)
		return;

	// Move towards the player
	
	ControlledTank->AimAt(PlayerTank->GetActorLocation());
	ControlledTank->Fire();  // TODO limit firing rate
}