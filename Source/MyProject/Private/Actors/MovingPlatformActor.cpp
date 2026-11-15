#include "Actors/MovingPlatformActor.h"
#include "Components/StaticMeshComponent.h"

AMovingPlatformActor::AMovingPlatformActor()
{
	PrimaryActorTick.bCanEverTick = true;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMesh");
	RootComponent = PlatformMesh;
}

void AMovingPlatformActor::BeginPlay()
{
	Super::BeginPlay();
	StartLocation = GetActorLocation();
}

void AMovingPlatformActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	RunningTime += DeltaTime * Speed;

	// Map Sine wave (-1 to 1) to a 0.0 -> 1.0 interpolation factor
	const float Alpha = (FMath::Sin(RunningTime) + 1.0f) * 0.5f;
	const FVector NewLocation = FMath::Lerp(StartLocation, StartLocation + MovementOffset, Alpha);

	SetActorLocation(NewLocation);
}