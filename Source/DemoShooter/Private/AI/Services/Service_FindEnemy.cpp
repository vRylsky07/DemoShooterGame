// DemoShooter. All right reserved.


#include "AI/Services/Service_FindEnemy.h"

UService_FindEnemy::UService_FindEnemy()
{
    NodeName = "Find Enemy";
};

void UService_FindEnemy::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = DS_Utils::GetComponentByUserClass<UDS_AIPerceptionComponent>(Controller);
        
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        };
    };
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
