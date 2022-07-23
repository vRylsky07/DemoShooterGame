// DemoShooter. All right reserved.


#include "Components/DSCharacterMovementComponent.h"
#include "Player/DemoShooterPlayerCharacter.h"

float UDSCharacterMovementComponent::GetMaxSpeed() const{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ADemoShooterPlayerCharacter *PlayerPointer = Cast<ADemoShooterPlayerCharacter>(GetPawnOwner());
    return PlayerPointer && PlayerPointer->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
};