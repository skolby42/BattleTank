// Copyright Scott Kolby 2020


#include "TankBarrel.h"

void UTankBarrel::Elevate(float DegreesPerSecond)
{
	UE_LOG(LogTemp, Warning, TEXT("Barrel Elevate called at speed %f"), DegreesPerSecond);
	// Move barrel the right amount this frame
	// Rotate barrel up/down given a max elevation speed and frame time
}