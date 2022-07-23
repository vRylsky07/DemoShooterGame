// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DS_FireDamageType.h"
#include "DS_IceDamageType.h"
#include "DS_CoreTypes.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "DS_Utils.h"
#include "Camera/CameraShakeBase.h"
#include "Perception/AISense_Damage.h"
#include "UI/DS_FloatingDamageWidget.h"
#include "DSHealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMOSHOOTER_API UDSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDSHealthComponent();

	float GetHealth() const
	{
	     return Health;
	 };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	bool bIsItPlayer = true;

	FOnDeathSignature OnDeath;
	FOnHealthChangedSignature OnHealthChanged;
	FTimerHandle AutoHealTimer;

	 UFUNCTION()
	 void DamageHandler(AActor *ActorPtr1, float Dmg1, const class UDamageType *DamageType1,
                     class AController *InstigatedBy, AActor *ActorEnemy1);

	 UFUNCTION(BlueprintCallable, Category = "Health")
	 bool IsDead() const
	 {
      return Health <= 0.0f;
	 };

	 UFUNCTION(BlueprintCallable, Category = "Health")
     float GetHealthPercent() const
     {
         return Health / MaxHealth;
     };

	 void SpawnDamageWidget(float DamageTaken, AController * InstigatedBy);
	
	 UFUNCTION()
	 void AutoHealFunc();

	 UFUNCTION(BlueprintCallable)
	 void SetHealth(float NewHp);

	 void ReportDamageEvent(float Damage, AController * InstigatedBy);
	 bool IsItDamage = false;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float MaxHealth = 5000.0f;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    float HealValue = 13.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    float HealUpdate = 0.2f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    float HealDelay = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
	float IncreaseHealInTime = 0.5f;
    float BaseIncreaseHealInTime;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI", meta = (EditCondition = "!bIsItPlayer"))
    TSubclassOf <UDS_FloatingDamageWidget> DamageTakenWidget;

private:
    float Health = 0.0f;
};
