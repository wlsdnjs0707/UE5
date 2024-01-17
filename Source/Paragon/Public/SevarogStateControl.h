// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemyStateControl.h"
#include <Kismet/GameplayStatics.h>
#include "SevarogStateControl.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGON_API USevarogStateControl : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USevarogStateControl();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float attackRange = 250;

	UPROPERTY(EditAnywhere)
	float findRange = 10000;

	UPROPERTY(EditAnywhere)
	float moveSpeed = 250;

	UPROPERTY(VisibleAnywhere)
	AActor* target = nullptr;

	UPROPERTY(VisibleAnywhere)
	State currentState = State::Wait;

	// C++ 함수를 블루프린트에서 호출하기
	UFUNCTION(BlueprintCallable)
	State ReturnState();

	UPROPERTY(EditAnywhere)
	float dashCooldown = 0;

	UPROPERTY(EditAnywhere)
	float grabCooldown = 0;

	bool isDash;
	bool isGrab;

	UPROPERTY(EditAnywhere)
	float dashCasting = 0;

	UPROPERTY(EditAnywhere)
	float grabCasting = 0;
		
};
