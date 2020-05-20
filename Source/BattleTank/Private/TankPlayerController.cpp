// Copyright Scott Kolby 2020

#include "TankPlayerController.h"
#include "Engine/World.h"
#include "Math/Vector2D.h"
#include "Tank.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	ATank* ControlledTank = GetControlledTank();
	if (!ControlledTank)
		UE_LOG(LogTemp, Error, TEXT("Player controller controlled tank not found!"))
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshairs();
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshairs()
{
	if (!GetControlledTank())
		return;

	FVector HitLocation;
	
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	FVector2D ScreenLocation(ViewPortSizeX * CrosshairXLocation, ViewPortSizeY * CrosshairYLocation);
	FVector LookDirection;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		//UE_LOG(LogTemp, Warning, TEXT("LookDirection: %s"), *LookDirection.ToString())
		return GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	HitLocation = FVector(0.f);
	return false;
}

bool ATankPlayerController::GetLookDirection(const FVector2D& ScreenLocation, FVector& LookDirection) const
{
	// De-project the screen position of the crosshair to a world direction
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceRange;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetControlledTank());  // Ignore controlled tank

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility,
		TraceParams
	))
	{
		HitLocation = HitResult.Location;
		//UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitResult.GetActor()->GetName());
		return true;
	};

	return false;
}