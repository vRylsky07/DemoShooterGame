// DemoShooter. All right reserved.


#include "AI/EnvQueryTest_CanTakePickup.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_VectorBase.h"

UEnvQueryTest_CanTakePickup::UEnvQueryTest_CanTakePickup(const FObjectInitializer &ObjectInitializer)
    : Super(ObjectInitializer){

    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_VectorBase::StaticClass();
    SetWorkOnFloatValues(false);
};

void UEnvQueryTest_CanTakePickup::RunTest(FEnvQueryInstance &QueryInstance) const
{
    const auto DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    bool bWantsHit = BoolValue.GetValue();

    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto *ItemActor = GetItemActor(QueryInstance, It.GetIndex());
        const auto PickupActor = Cast<ADS_HealthPickup>(ItemActor);
        if (!PickupActor)
            continue;

        const auto CanBeTaken = PickupActor->CanBeTaken();
        It.SetScore(TestPurpose, FilterType, CanBeTaken, bWantsHit);
    };
    return;
}
