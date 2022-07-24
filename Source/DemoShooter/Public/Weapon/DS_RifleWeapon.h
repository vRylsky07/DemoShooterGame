// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/DS_BaseWeapon.h"
#include "Weapon/Components/DSWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "DS_RifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class DEMOSHOOTER_API ADS_RifleWeapon : public ADS_BaseWeapon
{
	GENERATED_BODY()

	public:

        ADS_RifleWeapon();

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle Stats")
        float TimeBetweenShoot = 0.1f;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle Stats")
        int Recoil = 100;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle Stats")
        int RecoilMultiplyInMove = 8;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle Stats")
        float Damage = 100.0f;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
        USoundBase * ShootSound;

        UPROPERTY(VisibleAnywhere, Category = "VFX")
        UDSWeaponFXComponent * WeaponFXComponent;

        UPROPERTY(EditDefaultsOnly, Category = "VFX")
        UNiagaraSystem *TraceEffect;

        UPROPERTY(EditDefaultsOnly, Category = "VFX")
        FString TraceEndLocation = "TraceEndLocation";

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
        TSubclassOf<UCameraShakeBase> CameraShake;

        UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI Weapon Settings")
        bool AIWeapon = false;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Weapon Settings", meta = (EditCondition = "AIWeapon"))
        float MaxDistanceRecoilReduce = 2000.0f;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Weapon Settings", meta = (ClampMin = "0.0", ClampMax = "1.0", EditCondition = "AIWeapon"))
        float MaxPercentRecoilReduce = 0.8;

        UPROPERTY()
        UNiagaraComponent * MuzzleFXComponent;

        int32 NoRecoilShootsCount = 0;

		FTimerHandle ShootTimerHandle;

        void MakeDamage();
        void SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd);
        void InitMuzzleFX();
        void SetMuzzleFXVisibility(bool Visibility);
        AController* GetController() const;

        virtual void BeginPlay() override;
		virtual void StartFire() override;
        virtual void StopFire() override;
        virtual void MakeShot() override;
        virtual bool GetTraceData(FVector &ViewLocation, FVector &ViewRotation, FVector &TraceEnd) override;
	
};
