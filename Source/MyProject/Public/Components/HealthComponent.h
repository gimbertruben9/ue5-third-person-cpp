#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

/**
 * Modular health component that manages actor health points and destruction upon death.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UHealthComponent();

	// Applies damage to this component and destroys the owner if health drops below zero
	void ApplyDamage(float DamageAmount);

protected:
	// Current and initial health value of the owning actor
	UPROPERTY(EditAnywhere, Category = "Health Settings")
	float Health = 100.0f;
};