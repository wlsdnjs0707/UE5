// Fill out your copyright notice in the Description page of Project Settings.


#include "HitReaction.h"

// Sets default values for this component's properties
UHitReaction::UHitReaction()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHitReaction::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	hitMontage = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/MyAsset/Animation/MinionHit.MinionHit"));
	deathMontage = LoadObject<UAnimMontage>(nullptr, TEXT("/Game/MyAsset/Animation/MinionDeath.MinionDeath"));

	character = Cast<ACharacter>(GetOwner());
	animInstance = character->GetMesh()->GetAnimInstance();
	characterMovementComponent = character->GetCharacterMovement();
}


// Called every frame
void UHitReaction::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	if (hitTimer > 0)
	{
		hitTimer -= DeltaTime;
	}

	if (hitTimer <= 0)
	{
		if (!isBoss)
		{
			characterMovementComponent->MaxWalkSpeed = 250.0f;
		}
	}
}

void UHitReaction::Hit(float damage)
{
	if (health <= 0)
	{
		return;
	}

	if (animInstance && hitMontage)
	{
		if (!isBoss)
		{
			characterMovementComponent->MaxWalkSpeed = 0.0f;
		}
		
		hitTimer = 0.5f;

		health -= damage;

		FOutputDeviceNull pAR;

		if (health <= 0)
		{
			if (!isBoss)
			{
				animInstance->Montage_Play(deathMontage);

				// C++에서 블루프린트 커스텀 이벤트 호출하기
				GetOwner()->CallFunctionByNameWithArguments(TEXT("MinionDeath"), pAR, nullptr, true);
			}
			else
			{
				GetOwner()->CallFunctionByNameWithArguments(TEXT("SevaDeath"), pAR, nullptr, true);
			}
		}
		else
		{
			if (!isBoss)
			{
				animInstance->Montage_Play(hitMontage);

				// C++에서 블루프린트 커스텀 이벤트 호출하기
				GetOwner()->CallFunctionByNameWithArguments(TEXT("MinionHit"), pAR, nullptr, true);
			}
			else
			{
				GetOwner()->CallFunctionByNameWithArguments(TEXT("SevaHit"), pAR, nullptr, true);
			}
		}

		if (hitParticle != nullptr)
		{
			if (!isBoss)
			{
				UGameplayStatics::SpawnEmitterAtLocation(this, hitParticle, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation());
			}
			else
			{
				FVector spawnLocation = FVector(GetOwner()->GetActorLocation().X, GetOwner()->GetActorLocation().Y, GetOwner()->GetActorLocation().Z + 100.0f);
				UGameplayStatics::SpawnEmitterAtLocation(this, hitParticle, spawnLocation, GetOwner()->GetActorRotation());
			}
		}

		UE_LOG(LogTemp, Display, TEXT("Health : %f"), health);
	}
}

