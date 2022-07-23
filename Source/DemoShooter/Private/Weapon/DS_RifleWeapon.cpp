// DemoShooter. All right reserved.

#include "Weapon/DS_RifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Player/DemoShooterPlayerCharacter.h"
#include "GameFramework/Pawn.h"
#include "DS_Utils.h"
#include "Components/DSHealthComponent.h"
#include "Kismet/GameplayStatics.h"


ADS_RifleWeapon::ADS_RifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UDSWeaponFXComponent>("WeaponFXComponent");
};

void ADS_RifleWeapon::BeginPlay(){
    Super::BeginPlay();

    check(WeaponFXComponent);
};


void ADS_RifleWeapon::StartFire()
{
    FireAfterPause = true;
    GetWorldTimerManager().SetTimer(ShootTimerHandle, this, &ADS_BaseWeapon::MakeShot, TimeBetweenShoot, true);
    MakeShot();
    if (!ReloadInProgress && !IsAmmoEmpty())
    {
        InitMuzzleFX();
    };
}

void ADS_RifleWeapon::StopFire()
{
    FireAfterPause = false;
    GetWorldTimerManager().ClearTimer(ShootTimerHandle);
    NoRecoilShootsCount = 0;
    SetMuzzleFXVisibility(false);
};

void ADS_RifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
        return;
    if (!GetTraceData(TraceStart, TraceDirection, TraceEnd))
        return;
    if (FireAfterPause && ReloadInProgress)
    {
        NoRecoilShootsCount = 0;
        SetMuzzleFXVisibility(false);
        return;
    };

    if (ShootSound)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), ShootSound);
    };

    MakeHit(HitResult, TraceStart, TraceEnd);

    const auto HealthComponent = DS_Utils::GetComponentByUserClass<UDSHealthComponent>(Cast<APawn>(GetOwner()));
    DS_Utils::PlayCameraShake(GetOwner(), HealthComponent->IsDead(), CameraShake);


    if (HitResult.bBlockingHit && AngleToShoot())
    {
        //DrawDebugLine(GetWorld(), GetMuzzleSocketLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 3.0f, 0, 3.0f);
        MakeDamage();
        TraceEnd = HitResult.ImpactPoint;
        FVector FXScaleValue = {1.0f, 1.0f, 1.0f};
        WeaponFXComponent->PlayImpactFX(HitResult, FXScaleValue);
    }
    else
    {
        // DrawDebugLine(GetWorld(), GetMuzzleSocketLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    };
    SpawnTraceFX(GetMuzzleSocketLocation(), TraceEnd);
    DecreaseAmmo();
}

bool ADS_RifleWeapon::GetTraceData(FVector &ViewLocation, FVector &ViewRotation, FVector &TraceEndPoint)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character) return false;

    if (Character->IsPlayerControlled())
    {
        const auto Controller = GetPlayerController();
        if (!Controller)
            return false;

        FRotator RotatorToVector;
        Controller->GetPlayerViewPoint(ViewLocation, RotatorToVector);
        ViewRotation = RotatorToVector.Vector();
        TraceEndPoint = ViewLocation + ViewRotation * TraceDistance;

        auto Player = GetOwner();
        if (!Player)
            return false;

        if (Player->GetVelocity() != FVector::ZeroVector)
        {
            TraceEndPoint.Z =
                TraceEndPoint.Z + FMath::FRandRange(-Recoil * RecoilMultiplyInMove, Recoil * RecoilMultiplyInMove);
            TraceEndPoint.Y =
                TraceEndPoint.Y + FMath::FRandRange(-Recoil * RecoilMultiplyInMove, Recoil * RecoilMultiplyInMove);
            TraceEndPoint.X =
                TraceEndPoint.X + FMath::FRandRange(-Recoil * RecoilMultiplyInMove, Recoil * RecoilMultiplyInMove);
            return true;
        };

        if (NoRecoilShootsCount < 6)
        {
            TraceEndPoint.Z = TraceEndPoint.Z + FMath::FRandRange(-(Recoil / Recoil) * (NoRecoilShootsCount * 30),
                                                                  (Recoil / Recoil) * (NoRecoilShootsCount * 30));
            TraceEndPoint.Y = TraceEndPoint.Y + FMath::FRandRange(-(Recoil / Recoil) * (NoRecoilShootsCount * 50),
                                                                  (Recoil / Recoil) * (NoRecoilShootsCount * 50));
            TraceEndPoint.X = TraceEndPoint.X + FMath::FRandRange(-(Recoil / Recoil) * (NoRecoilShootsCount * 70),
                                                                  (Recoil / Recoil) * (NoRecoilShootsCount * 70));
            NoRecoilShootsCount++;
            return true;
        };

        TraceEndPoint.Z = TraceEndPoint.Z + FMath::FRandRange(-Recoil, Recoil);
        TraceEndPoint.Y = TraceEndPoint.Y + FMath::FRandRange(-Recoil, Recoil);
        TraceEndPoint.X = TraceEndPoint.X + FMath::FRandRange(-Recoil, Recoil);
    }
    else
    {
        GetAITraceData(ViewLocation, ViewRotation, TraceEndPoint);

        FCollisionQueryParams CollisionParams;
        FHitResult HResult;
        GetWorld()->LineTraceSingleByChannel(HResult, ViewLocation, TraceEndPoint, ECollisionChannel::ECC_Visibility,
                                             CollisionParams);

        FVector2D Distance2DVec = FVector2D(0.0f, MaxDistanceRecoilReduce);
        FVector2D Recoil2dVec = FVector2D(0.0f, Recoil * MaxPercentRecoilReduce);
        float DistanceToEndPoint = (HResult.ImpactPoint - ViewLocation).Size() > MaxDistanceRecoilReduce ? MaxDistanceRecoilReduce : (HResult.ImpactPoint - ViewLocation).Size();
        float MappedRecoil = FMath::GetMappedRangeValueClamped(Distance2DVec, Recoil2dVec, DistanceToEndPoint);
        float FinalRecoil = Recoil - MappedRecoil;

        TraceEndPoint.Z = TraceEndPoint.Z + FMath::FRandRange(-FinalRecoil, FinalRecoil);
        TraceEndPoint.Y = TraceEndPoint.Y + FMath::FRandRange(-FinalRecoil, FinalRecoil);
        TraceEndPoint.X = TraceEndPoint.X + FMath::FRandRange(-FinalRecoil, FinalRecoil);

    };

    return true;
}

void ADS_RifleWeapon::MakeDamage()
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor)
        return;

    DamagedActor->TakeDamage((Damage + FMath::FRandRange(0, Damage)), {}, GetPlayerController(), this);
}
void ADS_RifleWeapon::SpawnTraceFX(const FVector &TraceStartRef, const FVector &TraceEndRef)
{
    auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceEffect, TraceStartRef);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceEndLocation, TraceEndRef);
    };
};

void ADS_RifleWeapon::InitMuzzleFX(){
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    };
    SetMuzzleFXVisibility(true);
};

void ADS_RifleWeapon::SetMuzzleFXVisibility(bool Visibility){
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!Visibility);
        MuzzleFXComponent->SetVisibility(Visibility, true);
    };
};
