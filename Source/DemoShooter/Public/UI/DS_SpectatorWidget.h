// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_SpectatorWidget.generated.h"

UCLASS()
class DEMOSHOOTER_API UDS_SpectatorWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	bool GetRespawnTime(int32 &CountDownTime) const;
};
