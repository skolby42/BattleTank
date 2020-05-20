// Copyright Scott Kolby 2020


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	auto Time = GetWorld()->GetTimeSeconds();
	UE_LOG(LogTemp, Warning, TEXT("%f: Barrel Elevate called at speed %f"), Time, RelativeSpeed);
	// Move barrel the right amount this frame
	// Rotate barrel up/down given a max elevation speed and frame time
}