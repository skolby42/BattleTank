// Copyright Scott Kolby 2020

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()

protected:
	// Distance tank gets to player
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float AcceptanceRadius = 6000.f;

private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};
