// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* ControlledTank = GetControlledTank();

	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Error, TEXT("Cannot find Controlled Tank on %s"), *GetOwner()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Possessing %s tank"), *ControlledTank->GetName());
	}
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
		UE_LOG(LogTemp, Error, TEXT("HIT! Location is %s"), *HitLocation.ToString());
	}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	//bool Hit = false;
	//float Reach = 100000.f; 

	//FVector OutLocation;
	//FRotator OutRotation;

	//UCameraComponent* Camera = GetControlledTank()->FindComponentByClass<UCameraComponent>();

	//if (Camera)
	//{
	//	SViewport* Widget = GetWorld()->GetGameViewport()->GetGameViewportWidget().Get();

	//	GetPlayerViewPoint(OutLocation, OutRotation);

	//	FVector PlayerTankLocation = Camera->GetComponentLocation();
	//	FVector RayCastLocation = Camera->GetForwardVector() * Reach;
	//	FVector LineTraceEnd = PlayerTankLocation + RayCastLocation;

	//	FHitResult HitResult;

	//	DrawDebugLine(GetWorld(), PlayerTankLocation, LineTraceEnd, FColor(255, 0, 0, 0), false, -1, 0, 12.f);


	//	if (
	//		GetWorld()->LineTraceSingleByChannel(
	//			HitResult,
	//			PlayerTankLocation,
	//			LineTraceEnd,
	//			ECollisionChannel::ECC_Pawn,
	//			FCollisionQueryParams(TEXT(""), false, GetControlledTank())
	//		)
	//		)
	//	{
	//		Hit = true;
	//	}
	//}
	return false;
}