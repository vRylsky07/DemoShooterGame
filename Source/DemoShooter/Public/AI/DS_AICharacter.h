// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/DemoShooterPlayerCharacter.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Components/DS_AI_WeaponComponent.h"
#include "BrainComponent.h"
#include "DS_AICharacter.generated.h"

UCLASS()
class DEMOSHOOTER_API ADS_AICharacter : public ADemoShooterPlayerCharacter
{
    GENERATED_BODY()
    public:

    ADS_AICharacter(const FObjectInitializer &ObjectInit);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree * BT_Asset;

    virtual void OnDeath() override;
};
