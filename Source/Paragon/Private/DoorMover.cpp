// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorMover.h"

// Sets default values for this component's properties
UDoorMover::UDoorMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorMover::BeginPlay()
{
	Super::BeginPlay();

	// ...
	canMove = true;
}


// Called every frame
void UDoorMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (canMove)
	{
		FRotator currentRotation = GetOwner()->GetActorRotation();
		GetOwner()->AddActorLocalRotation(rotationVelocity * DeltaTime);
		rotateValue += DeltaTime;

		if (rotateValue >= 5.0f)
		{
			canMove = false;
		}
	}
}



