// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingActor.h"

// Sets default values
AMovingActor::AMovingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingActor::BeginPlay()
{
	Super::BeginPlay();

	startLocation = GetActorLocation();
}

// Called every frame
void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovingPlatform(DeltaTime);
	RotatingPlatform(DeltaTime);
}

void AMovingActor::MovingPlatform(float DeltaTime)
{
	FVector currentLocation = GetActorLocation();

	distance = FVector::Dist(currentLocation, startLocation);

	if (distance < 1000)
	{
		currentLocation.Z += 50 * DeltaTime;
		SetActorLocation(currentLocation);
	}
}

void AMovingActor::RotatingPlatform(float DeltaTime)
{
	AddActorLocalRotation(rotatingVelocity * DeltaTime);
}

