#include "Actors/ProjectileActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/Engine.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
	// Disable Tick to improve performance
	PrimaryActorTick.bCanEverTick = false;

	// 1. Configure the root collision sphere
	ProjectileCollisionComponent = CreateDefaultSubobject<USphereComponent>("ProjectileCollisionComponent");
	ProjectileCollisionComponent->InitSphereRadius(5.0f);
	ProjectileCollisionComponent->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileCollisionComponent->SetNotifyRigidBodyCollision(true);

	// Prevent characters from walking or stepping up on the projectile
	ProjectileCollisionComponent->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.0f));
	ProjectileCollisionComponent->CanCharacterStepUpOn = ECB_No;
	RootComponent = ProjectileCollisionComponent;

	// 2. Configure the visual mesh attached to the root
	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMeshComponent");
	ProjectileMeshComponent->BodyInstance.SetCollisionProfileName("NoCollision");
	ProjectileMeshComponent->SetupAttachment(RootComponent);

	// 3. Configure projectile movement
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->UpdatedComponent = ProjectileCollisionComponent;
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	// Automatically destroy the projectile after 3 seconds if it hits nothing
	InitialLifeSpan = 3.0f;
}

void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	// Bind the hit event dynamically
	ProjectileCollisionComponent->OnComponentHit.AddUniqueDynamic(this, &AProjectileActor::OnProjectileHit);
}

void AProjectileActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	ProjectileCollisionComponent->OnComponentHit.RemoveAll(this);
}

void AProjectileActor::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (GEngine && IsValid(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(
			-1,
			10.0f,
			FColor::Orange,
			FString::Printf(TEXT("Hit Actor: %s"), *OtherActor->GetName())
		);
	}

	Destroy();
}