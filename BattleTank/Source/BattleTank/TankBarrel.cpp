// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"



void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	float RotationToAdd = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float RawNewRotation = RelativeRotation.Pitch + RotationToAdd;

	float ClampedRotation = FMath::Clamp<float>(RawNewRotation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(ClampedRotation, 0, 0));
}
