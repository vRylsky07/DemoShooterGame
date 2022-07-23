// DemoShooter. All right reserved.


#include "Components/DS_AIPerceptionComponent.h"

AActor *UDS_AIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor *> PerceiveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
    if (PerceiveActors.Num() == 0)
    {
        GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PerceiveActors);
        if (PerceiveActors.Num() == 0)
        {
            return nullptr;
        };
    };

    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller) return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor *BestActor = nullptr;

    for (const auto ActorOne : PerceiveActors)
    {
        const auto HealthComponent = DS_Utils::GetComponentByUserClass<UDSHealthComponent>(ActorOne);
        if (HealthComponent && !HealthComponent->IsDead())
        {
            const auto CurrentDistance = (ActorOne->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestActor = ActorOne;
            };
        };
    };
    return BestActor;
};