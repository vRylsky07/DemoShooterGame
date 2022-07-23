// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "DS_Utils.h"
#include "Components/DS_WeaponComponent.h"
#include "Service_ChangeWeapon.generated.h"

UCLASS()
class DEMOSHOOTER_API UService_ChangeWeapon : public UBTService
{
	GENERATED_BODY()

	public:
    UService_ChangeWeapon();

	protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Probability = 0.5f;

	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
	
};
