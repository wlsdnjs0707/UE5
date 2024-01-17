// Fill out your copyright notice in the Description page of Project Settings.


#include "Grenade.h"

// Sets default values
AGrenade::AGrenade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));

	particleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleSystem"));

	explodeParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplodeParticle"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SM_Body(TEXT("/Game/ParagonTwinblast/Characters/Heroes/TwinBlast/Meshes/TwinBlast_Grenade.TwinBlast_Grenade"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_Trail(TEXT("/Game/ParagonTwinblast/FX/Particles/Abilities/VortexGrenade/FX/P_Twinblast_VortexGrenade_EngineIdle.P_Twinblast_VortexGrenade_EngineIdle"));
	static ConstructorHelpers::FObjectFinder<UParticleSystem> PS_Explode (TEXT("/Game/ParagonTwinblast/FX/Particles/Abilities/VortexGrenade/FX/P_TwinBlast_VortexGrenade_ExplodeBallistic.P_TwinBlast_VortexGrenade_ExplodeBallistic"));

	if (SM_Body.Succeeded())
	{
		body->SetStaticMesh(SM_Body.Object);
	}

	if (PS_Trail.Succeeded())
	{
		particleSystem->SetTemplate(PS_Trail.Object);
	}

	if (PS_Explode.Succeeded())
	{
		explodeParticle->SetTemplate(PS_Explode.Object);
	}

	RootComponent = body;
	particleSystem->SetupAttachment(body);
	particleSystem->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	explodeParticle->bAutoActivate = false;
	explodeParticle->DeactivateSystem();
	explodeParticle->SetupAttachment(body);

	body->SetRelativeScale3D(FVector(2.0f, 2.0f, 2.0f));
}

// Called when the game starts or when spawned
void AGrenade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrenade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (isLaunched)
	{
		moveSpeed = FMath::Lerp(moveSpeed, 2000.0f, 0.005f * DeltaTime);
	}
}

void AGrenade::LaunchGrenade(FVector target)
{
	targetLocation = target;
	targetVector = (targetLocation - GetActorLocation()).GetSafeNormal();
	isLaunched = true;
	GetWorld()->GetTimerManager().SetTimer(moveTimerHandle, this, &AGrenade::GrenadeMove, 0.005f, true);
}

void AGrenade::GrenadeMove()
{
	SetActorLocation(GetActorLocation() + targetVector * moveSpeed);

	if (FVector::Dist(GetActorLocation(), targetLocation) <= 10.0f)
	{
		GetWorld()->GetTimerManager().ClearTimer(moveTimerHandle);

		// 이펙트 출력
		explodeParticle->ActivateSystem();

		// 메시, trail 비활성화
		body->SetVisibility(false);
		particleSystem->DeactivateSystem();

		// 충돌 처리
		CollisionCheck();

		// 오브젝트 제거	
		FTimerHandle tempTimerHandle;

		GetWorld()->GetTimerManager().SetTimer(tempTimerHandle, [this]()
		{
				Destroy();
		}, 2.5f, false);
	}
}

void AGrenade::CollisionCheck()
{
	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(300.0f);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	TArray<FHitResult> hitResult;

	if (GetWorld()->SweepMultiByChannel(hitResult, GetActorLocation(), GetActorLocation(), FQuat::Identity, ECC_GameTraceChannel1, CollisionSphere, CollisionParams))
	{
		for (const FHitResult& hit : hitResult)
		{
			//UE_LOG(LogTemp, Display, TEXT("Hit : %s"), *(hit.GetActor()->GetActorNameOrLabel()));

			float damage = -0.5 * FVector::Dist(GetActorLocation(), hit.GetActor()->GetActorLocation()) + 175.0f;

			hit.GetActor()->FindComponentByClass<UHitReaction>()->Hit(damage);
		}

		//DrawDebugSphere(GetWorld(), GetActorLocation(), CollisionSphere.GetSphereRadius(), 32, FColor::Green, false, 2.5f);
	}
}
