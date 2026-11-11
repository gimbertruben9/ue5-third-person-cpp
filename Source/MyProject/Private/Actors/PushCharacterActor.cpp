#include "Actors/PushCharacterActor.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Engine/Engine.h"

// Sets default values
APushCharacterActor::APushCharacterActor()
{
	// Disable Tick as this actor reacts strictly to overlap events
	PrimaryActorTick.bCanEverTick = false;

	// Create the box component and set it as the root
	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	RootComponent = BoxComponent;

	// Ignore all collision channels except Pawns, which trigger Overlap events
	BoxComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void APushCharacterActor::BeginPlay()
{
	Super::BeginPlay();

	// Register dynamic callbacks for begin and end overlap events
	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this, &APushCharacterActor::BeginOverlap);
	BoxComponent->OnComponentEndOverlap.AddUniqueDynamic(this, &APushCharacterActor::EndOverlap);
}

void APushCharacterActor::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResults)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Green, TEXT("A Pawn has entered the trigger zone"));
	}

	// Cast the overlapping actor to ACharacter and launch it backward
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!IsValid(Character)) return;

	Character->LaunchCharacter(-OtherActor->GetActorForwardVector() * ForceImpulse, true, false);
}

void APushCharacterActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("A Pawn has left the trigger zone"));
	}
}