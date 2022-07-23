// DemoShooter. All right reserved.


#include "AI/Decorators/BTDecor_HealthPercent.h"
#include "BehaviorTree/Decorators/BTDecorator_Blackboard.h"

UBTDecor_HealthPercent::UBTDecor_HealthPercent()
{
    NodeName = "Health Percent";
};

bool UBTDecor_HealthPercent::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    AAIController * Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return false;

    const auto HealthComponent = Pawn->FindComponentByClass<UDSHealthComponent>();
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    float ResultFloat = HealthComponent->GetHealthPercent() - HealthValueToCheck;

    if (CheckType == CheckTypeEnum::LowerThenHealthValue)
    {
        if (ResultFloat < 0)
        {
            return true;
        };
        return false;
    };

    if (CheckType == CheckTypeEnum::BiggerThenHealthValue)
    {
        if (ResultFloat > 0)
        {
            return true;
        };
        return false;
        };

    return false;
}

