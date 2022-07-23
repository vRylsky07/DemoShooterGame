// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/DS_WeaponComponent.h"
#include "Weapon/DS_BaseWeapon.h"
#include "DS_AI_WeaponComponent.generated.h"

UCLASS()
class DEMOSHOOTER_API UDS_AI_WeaponComponent : public UDS_WeaponComponent
{
	GENERATED_BODY()
	
	virtual void NextWeapon() override;
    virtual void StartFire() override;
};
