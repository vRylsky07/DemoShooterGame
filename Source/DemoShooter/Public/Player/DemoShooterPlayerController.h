// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Components/DS_RespawnComponent.h"
#include "DemoShooterPlayerController.generated.h"

UCLASS()
class DEMOSHOOTER_API ADemoShooterPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ADemoShooterPlayerController();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UDS_RespawnComponent* RespawnComponent;
};
