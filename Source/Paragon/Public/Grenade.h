// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Rotator.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/Engine.h"
#include "HitReaction.h"
#include "Grenade.generated.h"

UCLASS()
class PARAGON_API AGrenade : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrenade();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* body;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* particleSystem;

	UPROPERTY(VisibleAnywhere)
	UParticleSystemComponent* explodeParticle;

	void LaunchGrenade(FVector target);

	void GrenadeMove();
	void CollisionCheck();

	// Grenade Move
	FVector targetLocation;
	float moveSpeed = 0.0f;
	FTimerHandle moveTimerHandle;
	FVector targetVector;
	bool isLaunched = false;
};
