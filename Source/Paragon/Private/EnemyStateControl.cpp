// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStateControl.h"
#include <Kismet/GameplayStatics.h>
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UEnemyStateControl::UEnemyStateControl()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyStateControl::BeginPlay()
{
	Super::BeginPlay();

	// ...
	target = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();
}


// Called every frame
void UEnemyStateControl::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (target == nullptr)
	{
		currentState = State::Wait;
	}
	else if (FVector::Distance(target->GetActorLocation(), GetOwner()->GetActorLocation()) < attackRange)
	{
		currentState = State::Attack;
	}
	else if (FVector::Distance(target->GetActorLocation(), GetOwner()->GetActorLocation()) < findRange)
	{
		currentState = State::Chase;
	}

	/*switch (currentState)
	{
	case State::Wait:
		break;
	case State::Chase:
		break;
	case State::Attack:
		break;
	default:
		break;
	}*/
}

State UEnemyStateControl::ReturnState()
{
	return currentState;
}
