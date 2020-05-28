// Copyright Scott Kolby 2020


#include "TankTrack.h"
#include "SprungWheel.h"
#include "SpawnPoint.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -1, 1);
	DriveTrack(CurrentThrottle);
}

void UTankTrack::DriveTrack(float Throttle)
{
	auto ForceApplied = Throttle * TrackMaxDrivingForce;
	auto Wheels = GetWheels();
	auto ForcePerWheel = 0.f;
	
	if (Wheels.Num() > 0)
		ForcePerWheel = ForceApplied / Wheels.Num();

	for (ASprungWheel* Wheel : Wheels)
	{
		Wheel->AddDrivingForce(ForcePerWheel);
	}
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	TArray<USceneComponent*> ChildComponents;
	GetChildrenComponents(true, ChildComponents);

	TArray<ASprungWheel*> Wheels;
	for (auto Component : ChildComponents)
	{
		auto SpawnPoint = Cast<USpawnPoint>(Component);
		if (!SpawnPoint) continue;
		
		auto SprungWheel = Cast<ASprungWheel>(SpawnPoint->GetSpawnedActor());
		if (SprungWheel)
		{
			Wheels.Add(SprungWheel);
		}
	}

	return Wheels;
}
