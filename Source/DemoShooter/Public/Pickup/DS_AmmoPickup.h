// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickup/DS_BasePickup.h"
#include "DS_Utils.h"
#include "DSHealthComponent.h"
#include "DS_WeaponComponent.h"
#include "DS_AmmoPickup.generated.h"


UCLASS()
class DEMOSHOOTER_API ADS_AmmoPickup : public ADS_BasePickup
{
	GENERATED_BODY()
	
	public:

		void AddSupplies(APawn *PlayerPawn) override;
};
