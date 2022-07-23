// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DS_CoreTypes.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "DS_Utils.h"
#include "Components/DS_AIPerceptionComponent.h"
#include "DS_BaseWeapon.generated.h"



class USkeletalMeshComponent;



UCLASS()
class DEMOSHOOTER_API ADS_BaseWeapon : public AActor
{
	GENERATED_BODY()

public:	
	ADS_BaseWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
    USkeletalMeshComponent * WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Battle Stats")
	float TraceDistance = 20000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{15, 10, false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem *MuzzleFX;

    FOnClipEmptySignature OnClipEmpty;

	FVector TraceStart;
	FHitResult HitResult;
    FVector TraceDirection;
    FVector TraceEnd;

    bool FireAfterPause = false;
    bool ReloadInProgress = false;
    bool CanInstantFireAfterReload = false;

	virtual void StartFire();
    virtual void StopFire();
    virtual void MakeShot();
    virtual bool GetTraceData(FVector &ViewLocation, FVector &ViewRotation, FVector &TraceEndPoint);

    void GetAITraceData(FVector &ViewLocation, FVector &ViewRotation, FVector &TraceEndPoint);
    void MakeHit(FHitResult &HResult, const FVector &TraceStartPoint, const FVector &TraceEndPoint);

    APlayerController *GetPlayerController() const;
    FVector GetMuzzleSocketLocation() const;
    FWeaponDataUI GetWeaponDataUI() {return UIData;};
    FAmmoData GetWeaponAmmoData() {return CurrentAmmo;};
    UNiagaraComponent *SpawnMuzzleFX();
    
    void DecreaseAmmo();
    void AddClipsToDefault();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    void ChangeClip();
    bool AngleToShoot();
    bool CanReload() const;



protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
    FWeaponDataUI UIData;

	virtual void BeginPlay() override;
  

private:
    FAmmoData CurrentAmmo;
};
