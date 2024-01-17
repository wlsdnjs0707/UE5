// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Misc/OutputDeviceNull.h"
#include "HitReaction.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGON_API UHitReaction : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHitReaction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void Hit(float damage);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float hitTimer = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float health = 100;

	ACharacter* character;
	UCharacterMovementComponent* characterMovementComponent;
	UAnimInstance* animInstance;
	UAnimMontage* hitMontage;
	UAnimMontage* deathMontage;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* hitParticle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isBoss = false;
};
