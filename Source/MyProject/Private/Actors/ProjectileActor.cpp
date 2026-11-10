#include "Actors/ProjectileActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
	// Disable Tick to improve performance as movement is handled by ProjectileMovementComponent
	PrimaryActorTick.bCanEverTick = false;

	// 1. Root collision sphere: must be RootComponent so ProjectileMovementComponent can detect collisions
	ProjectileCollisionComponent = CreateDefaultSubobject<USphereComponent>("ProjectileCollisionComponent");
	SetRootComponent(ProjectileCollisionComponent);
	ProjectileCollisionComponent->SetCollisionProfileName("BlockAll");
	ProjectileCollisionComponent->SetNotifyRigidBodyCollision(true); // Enables simulation hit events (OnComponentHit)

	// 2. Visual mesh attached to the root collision component
	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMeshComponent");
	ProjectileMeshComponent->SetupAttachment(RootComponent);
	ProjectileMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	// 3. Projectile movement configuration
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f; // Linear bullet trajectory without gravity drop
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	// Bind the hit event dynamically to handle collision responses
	ProjectileCollisionComponent->OnComponentHit.AddUniqueDynamic(this, &AProjectileActor::OnProjectileHit);

	// Automatically destroy the actor after 10 seconds if it hits nothing
	SetLifeSpan(10.0f);
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectileActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// Unbind delegates to avoid dangling references
	ProjectileCollisionComponent->OnComponentHit.RemoveAll(this);
}

void AProjectileActor::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	// Destroy the projectile upon impacting a blocking surface
	Destroy();
}