#include "Actors/EnemyActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/HealthComponent.h"

AEnemyActor::AEnemyActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Create the static mesh component as the root and ensure it blocks Visibility traces
	EnemyMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("EnemyMeshComponent");
	RootComponent = EnemyMeshComponent;
	EnemyMeshComponent->SetCollisionProfileName("BlockAll");

	// Create the health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}