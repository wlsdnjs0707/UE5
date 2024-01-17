// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillControl.h"

// Sets default values for this component's properties
USkillControl::USkillControl()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkillControl::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void USkillControl::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (Q_Timer >= 0)
	{
		Q_Timer -= DeltaTime;
	}

	if (R_Timer >= 0)
	{
		R_Timer -= DeltaTime;
	}

	startPoint = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 50;
	endPoint = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 750.0f;

	if (GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, hit))
	{
		cursorLocation = hit.Location;
	}
}

bool USkillControl::SetGrenade()
{
	if (isCastingQSkill || Q_Timer > 0)
	{
		return false;
	}

	isCastingQSkill = true;
	return true;
}

void USkillControl::CancelGrenade()
{
	isCastingQSkill = false;
}

void USkillControl::ThrowGrenade(FVector spawnLocation)
{
	Q_Timer = 10.0f;

	if (isCastingQSkill)
	{
		isCastingQSkill = false;

		FRotator spawnRotation = FRotationMatrix::MakeFromX(cursorLocation - spawnLocation).Rotator();
		spawnRotation = spawnRotation.Add(0.0f, -90.0f, 0.0f);

		// spawn Actor(BP_Grenade)
		grenade = GetWorld()->SpawnActor<AGrenade>(AGrenade::StaticClass(), spawnLocation, spawnRotation);

		// Grenade 에 발사 함수 호출
		grenade->LaunchGrenade(cursorLocation);
	}
}

void USkillControl::LaserBeam()
{
	if (R_Timer > 0)
	{
		return;
	}

	R_Timer = 10.0f;

	shotCount = 20;
	GetWorld()->GetTimerManager().SetTimer(laserTimerHandle, this, &USkillControl::LaserShot, 0.1f, true);
}

void USkillControl::LaserShot()
{
	shotCount -= 1;

	if (shotCount <= 0)
	{
		//UE_LOG(LogTemp, Display, TEXT("shot Off"));
		GetWorld()->GetTimerManager().ClearTimer(laserTimerHandle);
	}

	FCollisionShape sphere = FCollisionShape::MakeSphere(100);

	TArray<FHitResult> hits;
	bool hasHit = GetWorld()->SweepMultiByChannel(hits, startPoint, endPoint, FQuat::Identity, ECC_GameTraceChannel1, sphere);

	if (hasHit && hits.Num() > 0)
	{
		for (int i = 0; i < hits.Num(); i++)
		{
			// 맞은 액터의 Hit() 호출
			hitReaction = hits[i].GetActor()->FindComponentByClass<UHitReaction>();
			hitReaction->Hit(20.0f);
			//DrawDebugSphere(GetWorld(), hits[i].ImpactPoint, 20, 20, FColor::Green, false, 5);
		}
	}
}

FVector USkillControl::ReturnCursorLocation()
{
	return cursorLocation;
}

