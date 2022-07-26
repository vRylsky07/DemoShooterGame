// DemoShooter. All right reserved.


#include "AI/DS_AIController.h"



ADS_AIController::ADS_AIController()
{
    AIPerceptionComponent = CreateDefaultSubobject<UDS_AIPerceptionComponent>("DS_AIPerceptionComponent");
    SetPerceptionComponent(*AIPerceptionComponent);

    RespawnComponent = CreateDefaultSubobject<UDS_RespawnComponent>("DS_RespawnComponent");

    bWantsPlayerState = true;
};

void ADS_AIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    const auto DS_Character = Cast<ADS_AICharacter>(InPawn);
    if (DS_Character)
    {
        RunBehaviorTree(DS_Character->BT_Asset);
    };
}
void ADS_AIController::Tick(float DeltaTime){
    Super::Tick(DeltaTime);
    const auto AimActor = AIPerceptionComponent->GetClosestEnemy();
    SetFocus(GetFocusOnActor());
}
AActor *ADS_AIController::GetFocusOnActor()
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
};