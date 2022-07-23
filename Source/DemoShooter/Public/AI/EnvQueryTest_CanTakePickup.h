// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "Pickup/DS_BasePickup.h"
#include "Pickup/DS_HealthPickup.h"
#include "EnvQueryTest_CanTakePickup.generated.h"

/**
 * 
 */
UCLASS()
class DEMOSHOOTER_API UEnvQueryTest_CanTakePickup : public UEnvQueryTest
{
	GENERATED_BODY()
	
	public:

	UEnvQueryTest_CanTakePickup(const FObjectInitializer &ObjectInitializer);

	virtual void RunTest(FEnvQueryInstance &QueryInstance) const override;
};
