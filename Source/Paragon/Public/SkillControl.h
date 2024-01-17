// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Grenade.h"
#include "Components/SceneComponent.h"
#include "GameFramework/PlayerController.h"
#include "HitReaction.h"
#include "SkillControl.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGON_API USkillControl : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillControl();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	bool SetGrenade();

	UFUNCTION(BlueprintCallable)
	void CancelGrenade();

	UFUNCTION(BlueprintCallable)
	void ThrowGrenade(FVector spawnLocation);

	UFUNCTION(BlueprintCallable)
	void LaserBeam();

	void LaserShot();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Q_Timer = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float R_Timer = 0;

	bool isCastingQSkill = false;

	FHitResult hit;

	FVector startPoint;
	FVector endPoint;

	UFUNCTION(BlueprintCallable)
	FVector ReturnCursorLocation();

	FVector cursorLocation;

	AGrenade* grenade;

	class UHitReaction* hitReaction; // 액터 컴포넌트 포인터

	FTimerHandle laserTimerHandle;
	int shotCount = 0;
};
