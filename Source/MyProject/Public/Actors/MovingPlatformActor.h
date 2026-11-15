#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatformActor.generated.h"

class UStaticMeshComponent;

/**
 * Platform actor that oscillates smoothly between its start position and a target offset.
 */
UCLASS()
class MYPROJECT_API AMovingPlatformActor : public AActor
{
	GENERATED_BODY()

public:
	AMovingPlatformActor();

protected:
	// Visual and collision mesh for the platform
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* PlatformMesh;

	// Relative offset defining the destination point of the platform
	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	FVector MovementOffset = FVector(0.0f, 400.0f, 0.0f);

	// Movement speed of the platform
	UPROPERTY(EditAnywhere, Category = "Platform Settings")
	float Speed = 1.5f;

	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
	FVector StartLocation;
	float RunningTime = 0.0f;
};