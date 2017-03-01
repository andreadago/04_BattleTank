// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (!ensure(AimingComponent)) { return; }
	
	FoundAimingComponent(AimingComponent);
	
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );
	AimTowardCrosshair();
}


void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetPawn()) { return; } // e.g. if not possessing
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{

	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	float CrossHairX = ViewportSizeX * CrossHairXLocation;
	float CrossHairY = ViewportSizeY * CrossHairYLocation;

	FVector2D ScreenLocation = FVector2D(CrossHairX, CrossHairY);
	
	FVector LookDirection;
	FVector CameraWorldLocation;

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		return GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // To be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FVector CameraWorldLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLine = CameraWorldLocation + (LookDirection * LineTraceRange);

	FHitResult HitResult;

	////For debugging
	//DrawDebugLine(GetWorld(), CameraWorldLocation, EndLine, FColor(255, 0, 0, 0), false, -1, 0, 12.f);

	if (GetWorld()->LineTraceSingleByChannel(
			HitResult,
			CameraWorldLocation,
			EndLine,
			ECollisionChannel::ECC_Visibility)
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;

}

