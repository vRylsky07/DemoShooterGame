// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "DS_Utils.h"
#include "AIController.h"
#include "Components/DSHealthComponent.h"
#include "BTDecor_HealthPercent.generated.h"

UENUM(BlueprintType)
enum class CheckTypeEnum : uint8
{
    BiggerThenHealthValue UMETA(DisplayName = "BiggerThenHealthValue"),
    LowerThenHealthValue UMETA(DisplayName = "LowerThenHealthValue")
};


UCLASS() class DEMOSHOOTER_API UBTDecor_HealthPercent : public UBTDecorator
{
	GENERATED_BODY()
	
	public:

	UBTDecor_HealthPercent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthValueToCheck = 0.6f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TEnumAsByte<CheckTypeEnum> CheckType;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
};
