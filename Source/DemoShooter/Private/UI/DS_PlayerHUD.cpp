// DemoShooter. All right reserved.


#include "UI/DS_PlayerHUD.h"




float UDS_PlayerHUD::GetHealhPercent() const
{
    const auto HealthComponent = DS_Utils::GetComponentByUserClass<UDSHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent)return 0.0f;

    return HealthComponent->GetHealthPercent();
};

bool UDS_PlayerHUD::GetCurrentWeaponUIData(FWeaponDataUI &UIData) const
{
    const auto WeaponComponent = DS_Utils::GetComponentByUserClass<UDS_WeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;

    if (!WeaponComponent->GetCurrentWeaponUIData(UIData)) return false;
    
    return true;
}

bool UDS_PlayerHUD::GetCurrentWeaponAmmoData(FAmmoData &AmmoData) const
{
    const auto WeaponComponent = DS_Utils::GetComponentByUserClass<UDS_WeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    if (!WeaponComponent->GetCurrentWeaponAmmoData(AmmoData))
        return false;

    return true;
}

bool UDS_PlayerHUD::IsPlayerAlive() const
{
    const auto HealthComponent = DS_Utils::GetComponentByUserClass<UDSHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
};

bool UDS_PlayerHUD::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}


bool UDS_PlayerHUD::Initialize()
{
    if (GetOwningPlayer()) 
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UDS_PlayerHUD::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    };

        return Super::Initialize();
}


void UDS_PlayerHUD::OnHealthChanged(float Healh)
{
    const auto HealthComponent = DS_Utils::GetComponentByUserClass<UDSHealthComponent>(GetOwningPlayerPawn());
    if (HealthComponent && HealthComponent->IsItDamage)
    {
        OnTakeDamage();
    };
}
void UDS_PlayerHUD::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent = DS_Utils::GetComponentByUserClass<UDSHealthComponent>(NewPawn);
    if (HealthComponent)
    {
        HealthComponent->OnHealthChanged.AddUObject(this, &UDS_PlayerHUD::OnHealthChanged);
    };
}
;
