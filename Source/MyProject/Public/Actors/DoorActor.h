#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Interactuable.h"
#include "DoorActor.generated.h"

/**
 * Interactive door actor implementing the IInteractuable interface.
 */
UCLASS()
class MYPROJECT_API ADoorActor : public AActor, public IInteractuable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADoorActor();

	// C++ implementation of the IInteractuable interface method
	virtual void Interact_Implementation(AActor* Interactor) override;

protected:
	// Translation offset applied when opening or closing the door
	UPROPERTY(EditAnywhere, Category = "Settings")
	FVector DoorMovementOffset = FVector(0.0f, 0.0f, -250.0f);

	// Tracks the current state of the door (open or closed)
	bool bIsDoorOpen = false;

	// Moves the door actor based on its current open/close state
	void OpenCloseDoor();
};