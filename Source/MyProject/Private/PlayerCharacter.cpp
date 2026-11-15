#include "PlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SceneComponent.h"
#include "Components/HealthComponent.h"
#include "Components/GunComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Engine/LocalPlayer.h"
#include "Interfaces/Interactuable.h"
#include "DrawDebugHelpers.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	// Configure the spring arm (camera boom)
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	// Configure the follow camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	// Configure the modular gun component attached to the root
	GunComponent = CreateDefaultSubobject<UGunComponent>("GunComponent");
	GunComponent->SetupAttachment(RootComponent);

	// Attach the fire position scene component directly to the gun component
	FireSceneComponent = CreateDefaultSubobject<USceneComponent>("FireSceneComponent");
	FireSceneComponent->SetupAttachment(GunComponent);

	// Initialize player health component
	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Register the Enhanced Input Mapping Context to the local player subsystem
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to player inputs
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!IsValid(EnhancedInputComponent)) return;

	// Bind movement and camera look actions
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);

	// Bind jump actions
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

	// Bind weapon firing and interaction actions
	EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &APlayerCharacter::Fire);
	EnhancedInputComponent->BindAction(InteractionAction, ETriggerEvent::Started, this, &APlayerCharacter::Interact);
}

void APlayerCharacter::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	if (!IsValid(Controller)) return;

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void APlayerCharacter::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookVector = InputActionValue.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookVector.X);
		AddControllerPitchInput(LookVector.Y);
	}
}

void APlayerCharacter::Fire()
{
	if (IsValid(GunComponent))
	{
		GunComponent->Fire(FireSceneComponent);
	}

	/*
	FVector SpawnPos = FireSceneComponent->GetComponentLocation();
	FRotator SpawnRot = FireSceneComponent->GetComponentRotation();

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Owner = this;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::DontSpawnIfColliding;

	GetWorld()->SpawnActor<AProjectileActor>(ProjectileActorClass, SpawnPos, SpawnRot, SpawnInfo);
	*/
}

void APlayerCharacter::Interact()
{
	FVector StartLocation;
	FRotator Rotation;
	GetActorEyesViewPoint(StartLocation, Rotation);

	const FVector EndLocation = StartLocation + (Rotation.Vector() * 200.0f);

	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Yellow, false, 5.0f);

	const bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, Params);
	if (bHit)
	{
		AActor* HitActor = HitResult.GetActor();
		if (!IsValid(HitActor)) return;

		if (HitActor->GetClass()->ImplementsInterface(UInteractuable::StaticClass()))
		{
			IInteractuable::Execute_Interact(HitActor, this);
		}
	}
}