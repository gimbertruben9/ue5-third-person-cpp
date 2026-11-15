#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GunComponent.generated.h"

class USceneComponent;

/**
 * Modular weapon component inheriting from UStaticMeshComponent that performs hitscan (Line Trace) firing.
 */
UCLASS()
class MYPROJECT_API UGunComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UGunComponent();

	// Fires a line trace from the specified muzzle scene component
	void Fire(USceneComponent* FirePosComponent);

protected:
	// Maximum range of the weapon line trace
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float Distance = 1000.0f;

	// Damage applied to actors with a UHealthComponent upon hit
	UPROPERTY(EditDefaultsOnly, Category = "Settings")
	float Damage = 40.0f;
};