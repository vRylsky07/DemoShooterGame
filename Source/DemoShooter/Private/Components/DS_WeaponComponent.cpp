// DemoShooter. All right reserved.


#include "Components/DS_WeaponComponent.h"
#include "Animations/DS_EquipFinishedAnimNotify.h"
#include "Animations/DS_ReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"
#include "Weapon/DS_RifleWeapon.h"

constexpr static int32 WeaponNum = 2;

UDS_WeaponComponent::UDS_WeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;

}

void UDS_WeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    checkf(WeaponData.Num() == WeaponNum, TEXT("Our charecter can have only %i weapons!"), WeaponNum);

    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
    InitAnimations();
}


void UDS_WeaponComponent::SpawnWeapons()
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!GetWorld() || !Character) return;

    for (auto OneWeaponData : WeaponData)
    {
        ADS_BaseWeapon * Weapon = GetWorld()->SpawnActor<ADS_BaseWeapon>(OneWeaponData.WeaponClass);
        if (!Weapon) continue;

    Weapon->OnClipEmpty.AddUObject(this, &UDS_WeaponComponent::OnEmptyClip);
    Weapon->SetOwner(GetOwner());
    Weapons.Add(Weapon);
    AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    };

    if (!CurrentWeapon)return;
}

void UDS_WeaponComponent::AttachWeaponToSocket(ADS_BaseWeapon *Weapon, USceneComponent *SceneComponent, const FName &SocketName){
    
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
};

void UDS_WeaponComponent::EquipWeapon(int32 WeaponIndex){
    if (WeaponIndex < 0 || WeaponIndex > Weapons.Num()) return;

    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    };

    CurrentWeapon = Weapons[CurrentWeaponIndex];
    
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&](const FWeaponData &Data) { 
        return Data.WeaponClass == CurrentWeapon->GetClass();
    });
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAM);
};

void UDS_WeaponComponent::StartFire(){
    auto RifleWeapon = Cast<ADS_RifleWeapon>(CurrentWeapon); // to can fire after reload instantly
    if (RifleWeapon)
    {
        CurrentWeapon->StartFire();
        return;
    };

    if (!CanFire()) return;
    CurrentWeapon->StartFire();

};

void UDS_WeaponComponent::StopFire()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->StopFire();
};

void UDS_WeaponComponent::NextWeapon(){
    if (!CanEquip()) return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}
void UDS_WeaponComponent::Reload()
{
    ChangeClip();
}
bool UDS_WeaponComponent::GetCurrentWeaponUIData(FWeaponDataUI & UIData)
{
    if (!CurrentWeapon) return false;

    UIData = CurrentWeapon->GetWeaponDataUI();

    return true;
};

bool UDS_WeaponComponent::GetCurrentWeaponAmmoData(FAmmoData &AmmoData)
{
    if (!CurrentWeapon)
        return false;

    AmmoData = CurrentWeapon->GetWeaponAmmoData();

    return true;
}

void UDS_WeaponComponent::TryToAddAmmo()
{

    bool CurrentWeaponWasEmpty = (CurrentWeapon->GetWeaponAmmoData().Bullets == 0 && CurrentWeapon->GetWeaponAmmoData().Clips == 0);
    
    for (auto Weapon : Weapons)
    {
        if (!Weapon)
            continue;
        Weapon->AddClipsToDefault();
    };

    if (CurrentWeaponWasEmpty)
    {
        ReloadAnimInProgress = true;
        CurrentWeapon->ReloadInProgress = true;
        PlayAnimMontage(CurrentReloadAnimMontage);
    };

    return;
};

void UDS_WeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    };
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
};

void UDS_WeaponComponent::PlayAnimMontage(UAnimMontage *Animation){
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    Character->PlayAnimMontage(Animation);
};

void UDS_WeaponComponent::InitAnimations(){
    
       auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<UDS_EquipFinishedAnimNotify>(EquipAM);
       if (EquipFinishedNotify)
       {
           EquipFinishedNotify->OnNotified.AddUObject(this, &UDS_WeaponComponent::OnEquipFinished);
       }
       else
       {
           UE_LOG(LogTemp, Error, TEXT("Forgot to set EquipFinished AnimNotify"));
           checkNoEntry();
       };

       for (auto OneWeaponData : WeaponData)
       {
           auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<UDS_ReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
           if (!ReloadFinishedNotify)
           {
               UE_LOG(LogTemp, Error, TEXT("Forgot to set ReloadFinished AnimNotify"));
               checkNoEntry();
           };

           ReloadFinishedNotify->OnNotified.AddUObject(this, &UDS_WeaponComponent::OnReloadFinished);
       } 

};

void UDS_WeaponComponent::OnEquipFinished(USkeletalMeshComponent *MeshComp)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComp) return;
    EquipAnimInProgress = false;
};

void UDS_WeaponComponent::OnReloadFinished(USkeletalMeshComponent *MeshComp)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComp)
        return;
    ReloadAnimInProgress = false;
    CurrentWeapon->ReloadInProgress = false;
}
void UDS_WeaponComponent::OnEmptyClip(){
    ChangeClip();
}

void UDS_WeaponComponent::ChangeClip(){
    if (!CanReload())
        return;
    CurrentWeapon->ChangeClip();
    ReloadAnimInProgress = true;
    CurrentWeapon->ReloadInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}


bool UDS_WeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UDS_WeaponComponent::CanReload() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress && CurrentWeapon->CanReload();
}

bool UDS_WeaponComponent::CanFire() const {
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
};