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

        const auto PerceivePawn = Cast<APawn>(ActorOne);
        const auto AreEnemies = PerceivePawn && DS_Utils::AreEnemies(Controller, PerceivePawn->Controller);

        if (HealthComponent && !HealthComponent->IsDead() && AreEnemies)
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


