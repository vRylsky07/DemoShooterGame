#pragma once

#include "Components/DSHealthComponent.h"
#include "DS_PlayerState.h"
#include "GameFramework/Controller.h"

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

    bool static AreEnemies(AController* Controller1, AController* Controller2)
    {
        if (!Controller1 || !Controller2 || Controller1 == Controller2) return false;

        const auto PlayerState1 = Cast<ADS_PlayerState>(Controller1->PlayerState);
        const auto PlayerState2 = Cast<ADS_PlayerState>(Controller2->PlayerState);

        return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
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
