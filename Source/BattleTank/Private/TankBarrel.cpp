// Copyright Scott Kolby 2020


#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Move barrel the right amount this frame
	// Rotate barrel up/down given a max elevation speed and frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto RawNewElevation = GetRelativeRotation().Pitch + ElevationChange;
	auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);
	
	SetRelativeRotation(FRotator(Elevation, 0, 0));
}