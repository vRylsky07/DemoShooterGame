// DemoShooter. All right reserved.


#include "AI/Tasks/BT_RandomLocation.h"

UBT_RandomLocation::UBT_RandomLocation()
{
    NodeName = "Find Random Location";
};

EBTNodeResult::Type UBT_RandomLocation::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard) return EBTNodeResult::Failed;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return EBTNodeResult::Failed;

    const auto NavSys = UNavigationSystemV1::GetCurrent(Pawn);
    if (!NavSys) return EBTNodeResult::Failed;

    FNavLocation NavLocation;
    auto Location = Pawn->GetActorLocation();

    if (!SelfCenter)
    {
        auto CenterActor = Cast<AActor>(Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
        if (!CenterActor) return EBTNodeResult::Failed;
        Location = CenterActor->GetActorLocation();
    };

    const auto Found = NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation);

    if (!Found) return EBTNodeResult::Failed;

    Blackboard->SetValueAsVector(RandomLocationBB.SelectedKeyName, NavLocation.Location);
    return EBTNodeResult::Succeeded;
};