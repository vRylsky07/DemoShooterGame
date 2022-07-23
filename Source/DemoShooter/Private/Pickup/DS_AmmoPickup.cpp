// DemoShooter. All right reserved.


#include "Pickup/DS_AmmoPickup.h"

void ADS_AmmoPickup::AddSupplies(APawn *PlayerPawn)
{
    const auto HealthComponent = DS_Utils::GetComponentByUserClass<UDSHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead())
        return;

    const auto WeaponComponent = DS_Utils::GetComponentByUserClass<UDS_WeaponComponent>(PlayerPawn);
    if (!WeaponComponent)
        return;

    return WeaponComponent->TryToAddAmmo();
};