// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_CoreTypes.h"
#include "Components/DS_WeaponComponent.h"
#include "Components/DSHealthComponent.h"
#include "DS_Utils.h"
#include "DS_PlayerHUD.generated.h"

UCLASS()
class DEMOSHOOTER_API UDS_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()

	public:

    UPROPERTY(BlueprintReadOnly)
    UTexture2D *CrosshairIcon;

    UPROPERTY(BlueprintReadOnly)
    UTexture2D *MainIcon;

    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealhPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponUIData(FWeaponDataUI &UIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponAmmoData(FAmmoData &AmmoData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();

    virtual bool Initialize() override;

    void OnHealthChanged(float Healh);
};
