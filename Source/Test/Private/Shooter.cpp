
#include "Shooter.h"

// Sets default values for this component's properties
UShooter::UShooter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShooter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UShooter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	startPoint = GetComponentLocation() + GetForwardVector() * 50;
	endPoint = GetComponentLocation() + GetForwardVector() * attackRange;

	DrawDebugLine(GetWorld(), startPoint, endPoint, FColor::Red);
}

void UShooter::Shoot()
{
	FCollisionShape sphere = FCollisionShape::MakeSphere(50);
	//FHitResult hit;
	//bool hasHit = GetWorld()->SweepSingleByChannel(hit, startPoint, endPoint, FQuat::Identity, ECC_GameTraceChannel1, sphere);

	TArray<FHitResult> hits;
	bool hasHit = GetWorld()->SweepMultiByChannel(hits, startPoint, endPoint, FQuat::Identity, ECC_GameTraceChannel1, sphere);

	if (hasHit && hits.Num() > 0)
	{
		for (int i = 0; i < hits.Num(); i++)
		{
			UE_LOG(LogTemp, Display, TEXT("hit : %s"), *(hits[i].GetActor()->GetActorNameOrLabel()));
			DrawDebugSphere(GetWorld(), hits[i].ImpactPoint, 20, 20, FColor::Green, false, 5);
		}
	}
}

