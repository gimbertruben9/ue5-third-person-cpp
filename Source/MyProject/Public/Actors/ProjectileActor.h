#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjectileActor.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class UStaticMeshComponent;

/**
 * Physical projectile actor with custom collision profile and hit notification.
 */
UCLASS()
class MYPROJECT_API AProjectileActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AProjectileActor();

protected:
	// Sphere collision component acting as the root
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	USphereComponent* ProjectileCollisionComponent;

	// Visual mesh representation of the projectile
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UStaticMeshComponent* ProjectileMeshComponent;

	// Component handling automatic projectile movement
	UPROPERTY(VisibleDefaultsOnly, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called when the actor is removed from the world
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	// Callback executed when the collision component hits a blocking object
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
};