// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "AIController.h"
#include "DS_Utils.h"
#include "Components/DSHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"
#include "DS_AIPerceptionComponent.generated.h"

UCLASS()
class DEMOSHOOTER_API UDS_AIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
	public:
    AActor * GetClosestEnemy() const;
};
