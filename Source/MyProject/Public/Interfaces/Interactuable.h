#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactuable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractuable : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface for world objects that can be interacted with by an actor.
 */
class MYPROJECT_API IInteractuable
{
	GENERATED_BODY()

public:
	// BlueprintNativeEvent allows implementation in both C++ (via Interact_Implementation) and Blueprints
	UFUNCTION(BlueprintNativeEvent)
	void Interact(AActor* Interactor);
};