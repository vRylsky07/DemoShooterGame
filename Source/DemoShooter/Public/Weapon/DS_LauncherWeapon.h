// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/DS_BaseWeapon.h"
#include "DS_LauncherWeapon.generated.h"

class ADS_Projectile;

UCLASS()
class DEMOSHOOTER_API ADS_LauncherWeapon : public ADS_BaseWeapon
{
    GENERATED_BODY()

    public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ADS_Projectile> ProjectileClass;

    virtual void StartFire() override;
    virtual void StopFire() override;
    virtual void MakeShot() override;
};
