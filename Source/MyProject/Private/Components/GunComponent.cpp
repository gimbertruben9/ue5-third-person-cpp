#include "Components/GunComponent.h"
#include "Components/HealthComponent.h"
#include "GameFramework/Pawn.h"
#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"

UGunComponent::UGunComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void UGunComponent::Fire(USceneComponent* FirePosComponent)
{
	if (!IsValid(FirePosComponent)) return;

	FHitResult OutHit;

	const FVector StartPos = FirePosComponent->GetComponentLocation();

	// Use the muzzle Yaw rotation combined with the player controller's vertical Pitch aim
	FRotator ShootRotation = FirePosComponent->GetComponentRotation();
	if (const APawn* OwnerPawn = Cast<APawn>(GetOwner()))
	{
		ShootRotation.Pitch = OwnerPawn->GetControlRotation().Pitch;
	}

	const FVector EndPos = StartPos + ShootRotation.Vector() * Distance;

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	// Draw red debug line showing the trajectory of the shot
	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Red, false, 1.0f);

	// Perform hitscan raycast along the Visibility channel
	if (GetWorld()->LineTraceSingleByChannel(OutHit, StartPos, EndPos, ECC_Visibility, CollisionQueryParams))
	{
		if (OutHit.bBlockingHit && IsValid(OutHit.GetActor()))
		{
			AActor* HitActor = OutHit.GetActor();

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					10.0f,
					FColor::Orange,
					FString::Printf(
						TEXT("Hitting Actor: %s, Impact Point: %s, Impact Normal: %s"),
						*HitActor->GetName(),
						*OutHit.ImpactPoint.ToString(),
						*OutHit.ImpactNormal.ToString()
					)
				);
			}

			// If the hit actor has a HealthComponent, apply damage to it
			if (UHealthComponent* HealthComp = HitActor->FindComponentByClass<UHealthComponent>())
			{
				HealthComp->ApplyDamage(Damage);
			}
		}
	}
}