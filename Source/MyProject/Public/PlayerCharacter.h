#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Actors/ProjectileActor.h"
#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class USceneComponent;

/**
 * Main player character class handling movement, camera control, and weapon firing.
 */
UCLASS()
class MYPROJECT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Camera boom positioning the camera behind the character
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USpringArmComponent* SpringArmComponent;

	// Follow camera
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UCameraComponent* CameraComponent;

	// Scene component used as the projectile spawn point
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	USceneComponent* FireSceneComponent;

	// Input Mapping Context for character controls
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* DefaultMappingContext;

	// Movement Input Action
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* MoveAction;

	// Look / Camera rotation Input Action
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* LookAction;

	// Jump Input Action
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* JumpAction;

	// Weapon fire Input Action
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* FireAction;

	// Projectile class to spawn when firing
	UPROPERTY(EditDefaultsOnly, Category = "ProjectileConfig")
	TSubclassOf<AProjectileActor> ProjectileActorClass;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Handles forward and sideways movement inputs
	void Move(const FInputActionValue& InputActionValue);

	// Handles mouse look inputs (Yaw and Pitch)
	void Look(const FInputActionValue& InputActionValue);

	// Spawns a projectile from the FireSceneComponent
	void Fire();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Returns the player camera component for external systems (e.g., AnimInstance spine rotation)
	UCameraComponent* GetPlayerCameraComponent() const
	{
		return CameraComponent;
	}

	// Called to bind functionality to player inputs
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};