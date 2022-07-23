// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickup/DS_BasePickup.h"
#include "DS_Utils.h"
#include "DSHealthComponent.h"
#include "DS_HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class DEMOSHOOTER_API ADS_HealthPickup : public ADS_BasePickup
{
	GENERATED_BODY()
	
	public:

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Heal")
		float HealthToAdd = 2000;

		void AddSupplies(APawn *PlayerPawn) override;
};
