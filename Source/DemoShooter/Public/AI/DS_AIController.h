// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AI/DS_AICharacter.h"
#include "Components/DS_AIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "DS_AIController.generated.h"

UCLASS()
class DEMOSHOOTER_API ADS_AIController : public AAIController
{
    GENERATED_BODY()

    public:
    ADS_AIController();
	
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UDS_AIPerceptionComponent * AIPerceptionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";

	protected:
    virtual void OnPossess(APawn * InPawn) override;
    virtual void Tick(float DeltaTime) override;

    private:
    AActor *GetFocusOnActor();
};
