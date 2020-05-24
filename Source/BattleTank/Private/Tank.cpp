// Copyright Scott Kolby 2020


#include "Tank.h"
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

void ATank::BeginPlay()
{
	Super::BeginPlay();  // Needed for BP BeginPlay to run!

	Barrel = FindComponentByClass<UTankBarrel>();
}

void ATank::Fire()
{
	if (!ensure(Barrel))
		return;

	bool isReloaded = GetWorld()->GetTimeSeconds() - LastFireTime > ReloadTimeSeconds;
	//bool isReloaded = FPlatformTime::Seconds() - LastFireTime > ReloadTimeSeconds;  // Alternate

	if (!isReloaded)
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


