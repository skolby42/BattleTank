// Copyright Scott Kolby 2020


#include "Tank.h"
#include "TankAimingComponent.h"
#include "TankMovementComponent.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
	TankMovementComponent = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	if (!BarrelToSet)
		return;

	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	if (!TurretToSet)
		return;

	TankAimingComponent->SetTurretReference(TurretToSet);
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
