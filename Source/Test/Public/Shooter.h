// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Shooter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TEST_API UShooter : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShooter();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
	float attackRange = 500;
		
	UFUNCTION(BlueprintCallable)
	void Shoot();

	FVector startPoint;
	FVector endPoint;
};
