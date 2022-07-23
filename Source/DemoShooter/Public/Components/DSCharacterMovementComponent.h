// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DSCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class DEMOSHOOTER_API UDSCharacterMovementComponent : public UCharacterMovementComponent
{
    GENERATED_BODY()
  public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    float RunModifier = 2.0f;

    virtual float GetMaxSpeed() const override;
};

