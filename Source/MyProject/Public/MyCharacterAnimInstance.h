#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class APlayerCharacter;

UCLASS()
class MYPROJECT_API UMyCharacterAnimInstance : public UAnimInstance
{
    GENERATED_BODY()

protected:
    UPROPERTY()
    UCharacterMovementComponent* CharacterMovementComponent;

    UPROPERTY(BlueprintReadOnly)
    bool IsMovingCmasmas = false;

    UPROPERTY(BlueprintReadOnly)
    bool IsFallingCmasmas = false;

    UPROPERTY(BlueprintReadOnly)
    float VelocityCmasmas;

    UPROPERTY(BlueprintReadOnly)
    float ZVelocityCmasmas;

    UPROPERTY()
    APlayerCharacter* PlayerCharacter;

    UPROPERTY(BlueprintReadOnly)
    float XRotatorCmasmas;

	// Override the native begin play to initialize references
    virtual void NativeBeginPlay() override;
    virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};