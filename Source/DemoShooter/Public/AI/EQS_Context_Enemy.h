// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EQS_Context_Enemy.generated.h"

/**
 * 
 */
UCLASS()
class DEMOSHOOTER_API UEQS_Context_Enemy : public UEnvQueryContext
{
	GENERATED_BODY()
	
	public:
	
	virtual void ProvideContext(FEnvQueryInstance &QueryInstance, FEnvQueryContextData &ContextData) const override;

	protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName EnemyActorKeyName = "EnemyActor";
};
