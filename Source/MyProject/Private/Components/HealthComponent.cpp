#include "Components/HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/Engine.h"

UHealthComponent::UHealthComponent()
{
	// Disable Tick as health only changes when receiving damage
	PrimaryComponentTick.bCanEverTick = false;
}

void UHealthComponent::ApplyDamage(float DamageAmount)
{
	Health -= DamageAmount;

	if (AActor* Owner = GetOwner())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.0f,
				FColor::Cyan,
				FString::Printf(TEXT("%s took %.1f damage | Remaining Health: %.1f"), *Owner->GetName(), DamageAmount, Health)
			);
		}

		// Destroy the actor when its health is less than or equal to 0
		if (Health < 0.0f || FMath::IsNearlyZero(Health))
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					5.0f,
					FColor::Red,
					FString::Printf(TEXT("%s has been destroyed!"), *Owner->GetName())
				);
			}
			Owner->Destroy();
		}
	}
}