// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DS_RespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMOSHOOTER_API UDS_RespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDS_RespawnComponent();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Respawn(int32 RespawnTime);
	int32 GetRespawnCountDown() const { return RespawnCountDown; };
	bool IsRespawnInProgress() const;

private:
	FTimerHandle RespawnTimerHandle;

	int32 RespawnCountDown = 0;

	void RespawnTimerUpdate();

};
