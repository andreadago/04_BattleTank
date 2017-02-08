// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATank* GetControlledTank() const;
	
	virtual void BeginPlay() override;
	
	virtual void Tick(float DeltaSeconds) override;

private:

	// Start the tank moving the barrel so that a shot would hit where
	// the crosshair intersects the world
	void AimTowardCrosshair();

	// Ray-casting toward crosshair.
	// Returns true if it hits anything.
	bool GetSightRayHitLocation(FVector& OutHitVector) const;
};
