// DemoShooter. All right reserved.


#include "Weapon/DS_LauncherWeapon.h"
#include "DS_Projectile.h"
#include "Kismet/GameplayStatics.h"


void ADS_LauncherWeapon::StartFire()
{
    MakeShot();
};

void ADS_LauncherWeapon::StopFire()
{
};

void ADS_LauncherWeapon::MakeShot(){

    if (!GetWorld() || IsAmmoEmpty())
        return;
    if (!GetTraceData(TraceStart, TraceDirection, TraceEnd))
        return;

    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector ProjectileDirection = (EndPoint - GetMuzzleSocketLocation()).GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleSocketLocation());

    auto Projectile = GetWorld()->SpawnActorDeferred<ADS_Projectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(ProjectileDirection);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    };

    DecreaseAmmo();
    SpawnMuzzleFX();
};
