// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick( DeltaSeconds );
	AimTowardCrosshair();
}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardCrosshair()
{
	if (!GetControlledTank()) { return; }
	FVector HitLocation;

	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledTank()->AimAt(HitLocation);
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
		GetLookVectorHitLocation(LookDirection, OutHitLocation);
		

	}

	return true;
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
			ECollisionChannel::ECC_Visibility,
			FCollisionQueryParams(TEXT(""), false, GetControlledTank()))
		)
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;

}

