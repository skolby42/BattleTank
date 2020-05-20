// Copyright Scott Kolby 2020

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
		UE_LOG(LogTemp, Error, TEXT("AI controller controlled tank not found!"))

	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank)
		UE_LOG(LogTemp, Error, TEXT("AI controller can't find player tank!"))
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* PlayerTank = GetPlayerTank();
	ATank* ControlledTank = GetControlledTank();
	if (!PlayerTank || !ControlledTank)
		return;

	// Move towards the player
	
	ControlledTank->AimAt(PlayerTank->GetActorLocation());

	// Fire if ready
}

ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{	
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn)
		return nullptr;

	return Cast<ATank>(PlayerPawn);
}