// DemoShooter. All right reserved.


#include "Components/DS_AI_WeaponComponent.h"

void UDS_AI_WeaponComponent::NextWeapon()
{
    if (!CanEquip())
        return;

    int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

    while (NextIndex != CurrentWeaponIndex)
    {
        if (!Weapons[NextIndex]->IsAmmoEmpty()) break;

        NextIndex = (NextIndex + 1) % Weapons.Num();
    };
    
    if (CurrentWeaponIndex != NextIndex)
    {
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    };
}

void UDS_AI_WeaponComponent::StartFire()
{
    if (!CanFire())
        return;

    if (CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    };
}
