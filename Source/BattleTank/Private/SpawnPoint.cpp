// Copyright Scott Kolby 2020


#include "SpawnPoint.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
USpawnPoint::USpawnPoint()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


AActor* USpawnPoint::GetSpawnedActor() const
{
	return SpawnedActor;
}

// Called when the game starts
void USpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	FTransform Transform = GetComponentTransform();
	SpawnedActor = GetWorld()->SpawnActorDeferred<AActor>(SpawnClass, Transform, GetOwner());

	if (!SpawnedActor)
		return;
	SpawnedActor->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);

	UGameplayStatics::FinishSpawningActor(SpawnedActor, Transform);
}
