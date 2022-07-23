// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "DS_HUD.generated.h"

UCLASS()
class DEMOSHOOTER_API ADS_HUD : public AHUD
{
	GENERATED_BODY()

	public:
    virtual void DrawHUD() override;

	protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidget;

	virtual void BeginPlay() override;
	
	private:
    void DrawCrosshair();

};
