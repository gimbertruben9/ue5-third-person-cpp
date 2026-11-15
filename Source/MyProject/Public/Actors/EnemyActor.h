#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyActor.generated.h"

class UStaticMeshComponent;
class UHealthComponent;

/**
 * Static enemy actor represented by a cube mesh that takes damage and gets destroyed when health < 0.
 */
UCLASS()
class MYPROJECT_API AEnemyActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnemyActor();

protected:
	// Static mesh component representing the enemy body (cube)
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* EnemyMeshComponent;

	// Health component handling damage reception and destruction
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UHealthComponent* HealthComponent;
};