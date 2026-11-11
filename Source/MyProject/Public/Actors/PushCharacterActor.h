#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PushCharacterActor.generated.h"

class UBoxComponent;

/**
 * Trigger volume actor that detects Pawn overlaps and repels characters backward.
 */
UCLASS()
class MYPROJECT_API APushCharacterActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APushCharacterActor();

protected:
	// Box trigger volume used to detect Pawn overlaps
	UPROPERTY(EditAnywhere, Category = "Components")
	UBoxComponent* BoxComponent;

	// Impulse strength applied to repel the character upon entering the trigger
	UPROPERTY(EditAnywhere, Category = "Settings")
	float ForceImpulse = 1000.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Callback executed when an actor enters the trigger volume
	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults);

	// Callback executed when an actor leaves the trigger volume
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex);
};