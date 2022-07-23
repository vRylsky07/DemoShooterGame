// DemoShooter. All right reserved.


#include "AI/Services/Service_ChangeWeapon.h"

UService_ChangeWeapon::UService_ChangeWeapon()
{
    NodeName = "Change Weapon";
};

void UService_ChangeWeapon::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (Controller)
    {
        const auto WeaponComponent = DS_Utils::GetComponentByUserClass<UDS_WeaponComponent>(Controller->GetPawn());
        if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon();
        };
    };
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
};