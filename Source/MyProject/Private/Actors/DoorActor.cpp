#include "Actors/DoorActor.h"

// Sets default values
ADoorActor::ADoorActor()
{
	// Disable Tick as the door only updates position upon player interaction
	PrimaryActorTick.bCanEverTick = false;
}

void ADoorActor::Interact_Implementation(AActor* Interactor)
{
	// Toggle the door state and apply the position offset
	bIsDoorOpen = !bIsDoorOpen;
	OpenCloseDoor();
}

void ADoorActor::OpenCloseDoor()
{
	const FVector DoorLocation = GetActorLocation() + DoorMovementOffset * ((bIsDoorOpen) ? -1.0f : 1.0f);
	SetActorLocation(DoorLocation);
}