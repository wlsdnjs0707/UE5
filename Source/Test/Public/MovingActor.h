// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActor.generated.h"

UCLASS()
class TEST_API AMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FVector startLocation = FVector(0, 0, 0);

	UPROPERTY(VisibleAnywhere)
	float distance = 0;

	UPROPERTY(EditAnywhere)
	FRotator rotatingVelocity;

	void MovingPlatform(float deltaTime);

	void RotatingPlatform(float deltaTime);
};
