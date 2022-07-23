// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "DS_Utils.h"
#include "Components/DS_AIPerceptionComponent.h"
#include "Service_FindEnemy.generated.h"

UCLASS()
class DEMOSHOOTER_API UService_FindEnemy : public UBTService
{
    GENERATED_BODY()

    public:
    UService_FindEnemy();

    protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
      FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
