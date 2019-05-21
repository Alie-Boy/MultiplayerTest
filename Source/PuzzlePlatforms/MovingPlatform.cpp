// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
	PrimaryActorTick.bCanEverTick = true;

	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		SetReplicates(true);
		SetReplicateMovement(true);
	}

	GlobalStartLocation = GetActorLocation();
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
}

void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{		
		FVector CurrentLocation = GetActorLocation();

		float DistanceFromStartToTarget = (GlobalTargetLocation - GlobalStartLocation).Size();
		float DistanceFromStartToCurrent = (CurrentLocation - GlobalStartLocation).Size();

		if (DistanceFromStartToCurrent >= DistanceFromStartToTarget)
		{
			GlobalStartLocation += GlobalTargetLocation;
			GlobalTargetLocation = GlobalStartLocation - GlobalTargetLocation;
			GlobalStartLocation -= GlobalTargetLocation;
		}

		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		CurrentLocation += Direction * Speed * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}
