// Copyright Scott Kolby 2020

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
		UE_LOG(LogTemp, Error, TEXT("AI controller controlled tank not found!"))
	else
		UE_LOG(LogTemp, Warning, TEXT("AI controlled tank: %s"), *ControlledTank->GetName());

	ATank* PlayerTank = GetPlayerTank();
	if (!PlayerTank)
		UE_LOG(LogTemp, Error, TEXT("AI controller can't find player tank!"))
	else
		UE_LOG(LogTemp, Warning, TEXT("AI controller found player tank: %s"), *PlayerTank->GetName());
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