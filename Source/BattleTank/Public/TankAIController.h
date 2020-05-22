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
	
private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Distance tank gets to player
	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 3000.f;
};
