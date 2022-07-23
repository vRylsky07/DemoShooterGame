// DemoShooter. All right reserved.


#include "AI/DS_AICharacter.h"
#include "AI/DS_AIController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/DSCharacterMovementComponent.h"

ADS_AICharacter::ADS_AICharacter(const FObjectInitializer &ObjectInit)
    : Super(ObjectInit.SetDefaultSubobjectClass<UDS_AI_WeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ADS_AIController::StaticClass();

    HealthComponentPointer->bIsItPlayer = false;

    bUseControllerRotationYaw = false;

    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    };
}

void ADS_AICharacter::OnDeath()
{
    Super::OnDeath();

    const auto ControllerAI = Cast<AAIController>(Controller);
    if (ControllerAI && ControllerAI->BrainComponent)
    {
        ControllerAI->BrainComponent->Cleanup();
    };
}

