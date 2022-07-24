// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DemoShooterModeBase.h"
#include "DS_PlayerState.h"
#include "DS_GameModeDataWidget.generated.h"

/**
 * 
 */
UCLASS()
class DEMOSHOOTER_API UDS_GameModeDataWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentRoundNum() const;

	UFUNCTION(BlueprintCallable)
	int32 GetTotalRoundsNum() const;

	UFUNCTION(BlueprintCallable)
	int32 GetRoundsSecondsRemaining() const;

private:
	ADemoShooterModeBase* GetGameMode() const;
	ADS_PlayerState* GetPlayerState() const;

};
