// Fill out your copyright notice in the Description page of Project Settings.


#include "SevarogStateControl.h"

// Sets default values for this component's properties
USevarogStateControl::USevarogStateControl()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USevarogStateControl::BeginPlay()
{
	Super::BeginPlay();

	// ...
	target = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

	grabCooldown = 5.0f;
	dashCooldown = 10.0f;

	currentState = State::Wait;
}


// Called every frame
void USevarogStateControl::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (dashCooldown > 0)
	{
		dashCooldown -= DeltaTime;
	}
	if (grabCooldown > 0)
	{
		grabCooldown -= DeltaTime;
	}

	if (isDash)
	{
		dashCasting -= DeltaTime;

		if (dashCasting <= 0)
		{
			isDash = false;
		}
	}
	if (isGrab)
	{
		grabCasting -= DeltaTime;

		if (grabCasting <= 0)
		{
			isGrab = false;
		}
	}

	if (target == nullptr)
	{
		currentState = State::Wait;
	}
	else if (grabCooldown <= 0 && !isDash)
	{
		grabCooldown += 20.0f;
		dashCooldown += 10.0f;
		isGrab = true;
		grabCasting = 1.0f;
		currentState = State::Grab;
	}
	else if (dashCooldown <= 0 && !isGrab)
	{
		dashCooldown += 20.0f;
		grabCooldown += 5.0f;
		isDash = true;
		dashCasting = 1.0f;
		currentState = State::Dash;
	}
	else if (FVector::Distance(target->GetActorLocation(), GetOwner()->GetActorLocation()) < attackRange)
	{
		currentState = State::Attack;
	}
	else if (FVector::Distance(target->GetActorLocation(), GetOwner()->GetActorLocation()) < findRange && !isGrab && !isDash)
	{
		currentState = State::Chase;
	}
}

State USevarogStateControl::ReturnState()
{
	return currentState;
}

