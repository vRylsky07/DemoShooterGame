// DemoShooter. All right reserved.


#include "AI/Services/Service_Fire.h"

UService_Fire::UService_Fire(){
    NodeName = "Fire Service";
};

void UService_Fire::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (Controller)
    {
        const auto WeaponComponent = DS_Utils::GetComponentByUserClass<UDS_WeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        };

    };

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
