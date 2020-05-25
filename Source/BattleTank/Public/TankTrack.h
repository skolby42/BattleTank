// Copyright Scott Kolby 2020

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * TankTrack is used to set maximum driving force, and apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UTankTrack();

	virtual void BeginPlay() override;

	// Sets a throttle between -1 and +1
	UFUNCTION(BlueprintCallable)
	void SetThrottle(float Throttle);

	void DriveTrack();

	// Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 15000000.f;  // Assume 40 ton tank, 1g acceleration

	float CurrentThrottle = 0;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void ApplySidewaysForce();
};
