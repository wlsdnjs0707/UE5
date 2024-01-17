// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerMover.h"

// Sets default values for this component's properties
UPlayerMover::UPlayerMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerMover::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	rollMontage = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/MyAsset/Animation/TB_Roll.TB_Roll"));
	//deathMontage = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/MyAsset/Animation/MinionDeath.MinionDeath"));

	character = Cast<ACharacter>(GetOwner());
	animInstance = character->GetMesh()->GetAnimInstance();
}


// Called every frame
void UPlayerMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (spaceTimer >= 0)
	{
		spaceTimer -= DeltaTime;
	}
}

void UPlayerMover::Roll()
{
	animInstance->Montage_Play(rollMontage);

	if (spaceTimer > 0)
	{
		return;
	}

	spaceTimer = 5.0f;

	targetLocation = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 650;

	rollTime = 0.75f;
	GetWorld()->GetTimerManager().SetTimer(moveTimerHandle, this, &UPlayerMover::RollMove, 0.005f, true);
}

void UPlayerMover::RollMove()
{
	GetOwner()->SetActorLocation(FMath::VInterpTo(GetOwner()->GetActorLocation(), targetLocation, GetWorld()->GetDeltaSeconds(), moveSpeed));

	rollTime -= FApp::GetDeltaTime();

	if (rollTime <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(moveTimerHandle);
	}
}

