// Copyright Scott Kolby 2020


#include "TankTurret.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	// Move turret the right amount this frame
	// Rotate turret left/right given a max rotation speed and frame time
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	auto RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Rotation = GetRelativeRotation().Yaw + RotationChange;

	SetRelativeRotation(FRotator(0, Rotation, 0));
}