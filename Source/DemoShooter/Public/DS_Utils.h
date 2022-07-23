#pragma once

#include "Components/DSHealthComponent.h"

class DS_Utils
{
  public:
    template <typename T> 
    T static *GetComponentByUserClass(AActor *PlayerPawn)
    {
        if (!PlayerPawn)
            return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    };

void static PlayCameraShake(AActor *Actor, bool IsDead, TSubclassOf<UCameraShakeBase> CameraShake)
    {
        const auto Player = Cast<APawn>(Actor);
    if (!Player || IsDead)return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager)
        return;

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
    };

};
