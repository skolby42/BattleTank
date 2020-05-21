// Copyright Scott Kolby 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
    virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly)
	float CrosshairXLocation = 0.5;
	
	UPROPERTY(EditDefaultsOnly)
	float CrosshairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

	ATank* GetControlledTank() const;
	void AimTowardsCrosshairs();
	bool GetSightRayHitLocation(FVector& HitLocation) const;
	bool GetLookDirection(const FVector2D& ScreenLocation, FVector& LookDirection) const;
	bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const;
};
