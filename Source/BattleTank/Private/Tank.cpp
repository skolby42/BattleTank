// Copyright Scott Kolby 2020


#include "Tank.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Tank = CreateDefaultSubobject<UStaticMeshComponent>(FName("Tank"));
	SetRootComponent(Tank);

	DestroyedBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Destroyed Blast"));
	DestroyedBlast->SetupAttachment(RootComponent);
	DestroyedBlast->bAutoActivate = false;
}

float ATank::GetHealthPercent() const
{
	return (float)CurrentHealth / (float)StartingHealth;
}

void ATank::DestroyTimerElapsed()
{
	Destroy();
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = StartingHealth;
}

float ATank::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp<int32>(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	
	if (CurrentHealth <= 0)
	{
		if (!DestroyedBlast->bHasBeenActivated)
			DestroyedBlast->Activate();
		OnDeath.Broadcast();

		FTimerHandle DestroyTimerHandle;
		GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle, this, &ATank::DestroyTimerElapsed, DestroyDelay);
	}

	return DamageToApply;
}