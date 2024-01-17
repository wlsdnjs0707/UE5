// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyStateControl.generated.h"

UENUM(BlueprintType)
enum class State : uint8
{
	Wait,
	Chase,
	Attack,
	Dash,
	Grab
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGON_API UEnemyStateControl : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnemyStateControl();

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

	UPROPERTY(EditAnywhere)
	float moveSpeed = 100;

	UPROPERTY(VisibleAnywhere)
	AActor* target = nullptr;

	UPROPERTY(VisibleAnywhere)
	State currentState = State::Wait;

	// C++ 함수를 블루프린트에서 호출하기
	UFUNCTION(BlueprintCallable)
	State ReturnState();
};
