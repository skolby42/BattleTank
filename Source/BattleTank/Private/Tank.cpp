// Copyright Scott Kolby 2020


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::AimAt(FVector HitLocation)
{
	auto TankAimingComponent = GetOwner()->FindComponentByClass<UTankAimingComponent>();
	if (TankAimingComponent)
		TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReloaded = GetWorld()->GetTimeSeconds() - LastFireTime > ReloadTimeSeconds;
	//bool isReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeSeconds;  // Alternate

	if (!Barrel || !isReloaded)
		return;

	// Spawn a projectile at the socket location
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(
		ProjectileBlueprint,
		Barrel->GetSocketLocation(FName("Projectile")), 
		Barrel->GetSocketRotation(FName("Projectile")));

	Projectile->Launch(LaunchSpeed);

	LastFireTime = GetWorld()->GetTimeSeconds();
	//LastFireTime = FPlatformTime::Seconds();
}
