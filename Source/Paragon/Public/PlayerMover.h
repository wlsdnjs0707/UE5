// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Character.h"
#include "Engine/Engine.h"
#include "PlayerMover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGON_API UPlayerMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Roll();

	ACharacter* character;
	UAnimInstance* animInstance;
	UAnimMontage* rollMontage;
	UAnimMontage* deathMontage;

	void RollMove();

	FVector targetLocation;
	float moveSpeed = 1.25f;

	FTimerHandle moveTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float spaceTimer = 0;

	float rollTime = 0;
};
