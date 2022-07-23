// DemoShooter. All right reserved.


#include "Pickup/DS_HealthPickup.h"

void ADS_HealthPickup::AddSupplies(APawn *PlayerPawn)
{
    const auto HealthComponent = DS_Utils::GetComponentByUserClass<UDSHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead())
        return;

    HealthComponent->SetHealth(HealthComponent->GetHealth() + HealthToAdd);
    return;
};