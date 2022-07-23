// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "DS_Utils.h"
#include "Components/DS_WeaponComponent.h"
#include "Service_Fire.generated.h"

/**
 * 
 */
UCLASS()
class DEMOSHOOTER_API UService_Fire : public UBTService
{
	GENERATED_BODY()

	public:
    UService_Fire();

	protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
