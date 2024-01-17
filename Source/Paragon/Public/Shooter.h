// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/SkeletalMeshSocket.h"
#include "HitReaction.h"
#include "Shooter.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGON_API UShooter : public USceneComponent
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
		
	UPROPERTY(EditAnywhere)
	float attackDamage = 20;
		
	UFUNCTION(BlueprintCallable)
	void Shoot();

	FVector startPoint;
	FVector endPoint;

    class UHitReaction* hitReaction; // 액터 컴포넌트 포인터

	UPROPERTY(EditAnywhere)
	class UParticleSystem* trailParticle;

	//USkeletalMeshSocket* gunMuzzleSocket;
};
