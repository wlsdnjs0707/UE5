// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyState.h"
#include <Kismet/GameplayStatics.h>

// Sets default values for this component's properties
UEnemyState::UEnemyState()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnemyState::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	target = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetPawn();

}


// Called every frame
void UEnemyState::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (target == nullptr)
	{
		currentState = Wait;
	}
	else if (FVector::Distance(target->GetActorLocation(), GetOwner()->GetActorLocation()) < attackRange)
	{
		currentState = Attack;
	}
	else if (FVector::Distance(target->GetActorLocation(), GetOwner()->GetActorLocation()) < findRange)
	{
		currentState = Chase;
	}

	switch (currentState)
	{
	case Wait:
		//UE_LOG(LogTemp, Display, TEXT("State : Wait"));
		break;
	case Chase:
		//UE_LOG(LogTemp, Display, TEXT("State : Chase"));
		break;
	case Attack:
		//UE_LOG(LogTemp, Display, TEXT("State : Attack"));
		break;
	default:
		break;
	}

	distance = FVector::Distance(target->GetActorLocation(), GetOwner()->GetActorLocation());
}

