// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Gameframework/Character.h"
#include "Weapon/DS_BaseWeapon.h"
#include "DS_CoreTypes.h"
#include "DS_WeaponComponent.generated.h"

class ADS_BaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMOSHOOTER_API UDS_WeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDS_WeaponComponent();

    UPROPERTY()
    ADS_BaseWeapon *CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<ADS_BaseWeapon *> Weapons;

    virtual void NextWeapon();
	virtual void StartFire();
	void StopFire();
	void Reload();

    bool CanFire() const;
    bool CanEquip() const;
    bool GetCurrentWeaponUIData(FWeaponDataUI &UIData);
    bool GetCurrentWeaponAmmoData(FAmmoData &AmmoData);
    void TryToAddAmmo();

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	FName WeaponEquipSocketName = "WeaponSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
    UAnimMontage * EquipAM;

    int32 CurrentWeaponIndex = 0;

	bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

	void AttachWeaponToSocket(ADS_BaseWeapon *Weapon, USceneComponent *SceneComponent, const FName &SocketName);
    void EquipWeapon(int32 WeaponIndex);

	virtual void BeginPlay() override;

    bool CanReload() const;

	private:

	UPROPERTY()
    UAnimMontage *CurrentReloadAnimMontage = nullptr;

	void SpawnWeapons();
    void PlayAnimMontage(UAnimMontage * Animation);
    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent *MeshComp);
    void OnReloadFinished(USkeletalMeshComponent *MeshComp);
    void OnEmptyClip();
    void ChangeClip();

};

