
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
	//gunMuzzleSocket = Cast<ACharacter>(GetOwner())->GetMesh()->GetSocketByName(SocketName);
}


// Called every frame
void UShooter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	startPoint = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * 50;
	endPoint = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * attackRange;

	//DrawDebugLine(GetWorld(), startPoint, endPoint, FColor::Red);
}

void UShooter::Shoot()
{
	FCollisionShape sphere = FCollisionShape::MakeSphere(50);

	TArray<FHitResult> hits;
	bool hasHit = GetWorld()->SweepMultiByChannel(hits, startPoint, endPoint, FQuat::Identity, ECC_GameTraceChannel1, sphere);
	// ECC_GameTraceChannel1 = Enemy

	//if (trailParticle != nullptr)
	//{
	//	UGameplayStatics::SpawnEmitterAtLocation(this, trailParticle, GetComponentLocation(), GetComponentRotation());
	//	//UE_LOG(LogTemp, Display, TEXT("SpawnEmitter"));
	//}

	if (hasHit && hits.Num() > 0)
	{
		for (int i = 0; i < hits.Num(); i++)
		{
			// 맞은 액터의 Hit() 호출
			hitReaction = hits[i].GetActor()->FindComponentByClass<UHitReaction>();
			hitReaction->Hit(attackDamage);
			//DrawDebugSphere(GetWorld(), hits[i].ImpactPoint, 20, 20, FColor::Green, false, 5);
		}
	}
}

