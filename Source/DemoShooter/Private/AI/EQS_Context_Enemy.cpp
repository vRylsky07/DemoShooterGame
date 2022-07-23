// DemoShooter. All right reserved.


#include "AI/EQS_Context_Enemy.h"

void UEQS_Context_Enemy::ProvideContext(FEnvQueryInstance &QueryInstance, FEnvQueryContextData &ContextData) const 
{
    const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
    if (!Blackboard)
        return;

    const auto ContextActor = Blackboard->GetValueAsObject(EnemyActorKeyName);

    UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
};