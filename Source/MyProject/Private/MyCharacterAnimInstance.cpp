#include "MyCharacterAnimInstance.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"

void UMyCharacterAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	// Cache references to the owning pawn and its movement component
	if (APawn* Pawn = TryGetPawnOwner())
	{
		CharacterMovementComponent = Pawn->GetComponentByClass<UCharacterMovementComponent>();
		PlayerCharacter = Cast<APlayerCharacter>(Pawn);
	}
}

void UMyCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// Guard against null references (critical in editor viewport and preview contexts)
	if (!IsValid(CharacterMovementComponent) || !IsValid(PlayerCharacter)) return;

	const FVector CharacterVelocity = CharacterMovementComponent->Velocity;

	// Calculate planar velocity (XY axis only, ignoring vertical motion)
	VelocityCmasmas = CharacterVelocity.Size2D();

	// Determine if the character is actively moving on the ground
	IsMovingCmasmas = VelocityCmasmas > 0.0f;

	// Extract vertical velocity for jump peak and falling transitions
	ZVelocityCmasmas = CharacterVelocity.Z;

	// Query whether the character is currently airborne
	IsFallingCmasmas = CharacterMovementComponent->IsFalling();

	// Read camera pitch rotation to drive dynamic spine aiming in the AnimGraph
	XRotatorCmasmas = -PlayerCharacter->GetPlayerCameraComponent()->GetComponentRotation().Pitch;
}