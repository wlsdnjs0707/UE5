// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyState.generated.h"

enum State
{
	Wait,
	Chase,
	Attack
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST_API UEnemyState : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyState();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float attackRange = 250;

	UPROPERTY(EditAnywhere)
	float findRange = 1000;

	UPROPERTY(VisibleAnywhere)
	AActor* target = nullptr;

	State currentState = Wait;

	UPROPERTY(VisibleAnywhere)
	float distance = 0;
};
