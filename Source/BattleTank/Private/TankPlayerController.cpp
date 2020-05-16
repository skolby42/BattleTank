// Copyright Scott Kolby 2020


#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
		UE_LOG(LogTemp, Error, TEXT("Player controller controlled tank not found!"))
	else
		UE_LOG(LogTemp, Warning, TEXT("Player controlled tank: %s"), *ControlledTank->GetName());
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}