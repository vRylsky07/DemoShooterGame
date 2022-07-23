// DemoShooter. All right reserved.


#include "Weapon/DS_BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"


ADS_BaseWeapon::ADS_BaseWeapon()
{
 	PrimaryActorTick.bCanEverTick = false;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ADS_BaseWeapon::BeginPlay()
{
	Super::BeginPlay();
    check(WeaponMesh);
    checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets can`t be less or equal zero"));
    checkf(DefaultAmmo.Clips >= 0, TEXT("Bullets can`t be less than zero"));
    CurrentAmmo = DefaultAmmo;
	
}

void ADS_BaseWeapon::StartFire(){};

void ADS_BaseWeapon::StopFire(){};

void ADS_BaseWeapon::MakeShot(){};

bool ADS_BaseWeapon::AngleToShoot()
{
    const FVector GunVector = ((GetMuzzleSocketLocation() + TraceDirection * TraceDistance) - GetMuzzleSocketLocation()).GetSafeNormal();
    const FVector VictimVector = (HitResult.ImpactPoint - GetMuzzleSocketLocation()).GetSafeNormal();
    const float Degrees = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(GunVector, VictimVector))); 
    return Degrees < 90.0f ? true : false;
}
bool ADS_BaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
};

APlayerController * ADS_BaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player)
        return nullptr;

    return Player->GetController<APlayerController>();
};

bool ADS_BaseWeapon::GetTraceData(FVector &ViewLocation, FVector &ViewRotation, FVector &TraceEndPoint)
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
    }
    else
    {
        GetAITraceData(ViewLocation, ViewRotation, TraceEndPoint);
    };


    return true;
};

FVector ADS_BaseWeapon::GetMuzzleSocketLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}
UNiagaraComponent *ADS_BaseWeapon::SpawnMuzzleFX()
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, 
        WeaponMesh,
        MuzzleSocketName, 
        FVector::ZeroVector, 
        FRotator::ZeroRotator, 
        EAttachLocation::SnapToTarget, 
        true);
}
void ADS_BaseWeapon::DecreaseAmmo()
{

    if (CurrentAmmo.Bullets == 0)
    {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, TEXT("--------------Clip is empty!--------------"));
        return;
    };

    CurrentAmmo.Bullets--;

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        OnClipEmpty.Broadcast();
    };
}

void ADS_BaseWeapon::AddClipsToDefault()
{
    CurrentAmmo.Clips = DefaultAmmo.Clips;
    if (CurrentAmmo.Bullets == 0)
    {
        CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    };
}

bool ADS_BaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ADS_BaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

void ADS_BaseWeapon::ChangeClip()
{
    if (!CurrentAmmo.Infinite)
    {
        if (CurrentAmmo.Clips == 0)
        {
            if (GEngine)
                GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Yellow, TEXT("--------------No more clips!--------------"));
            return;
        };
        CurrentAmmo.Clips--;
    };


    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

void ADS_BaseWeapon::GetAITraceData(FVector &ViewLocation, FVector &ViewRotation, FVector &TraceEndPoint)
{
    const auto AICharacter = Cast<ACharacter>(GetOwner());
    if (!AICharacter)
        return;

    const auto Controller = AICharacter->GetController<AAIController>();
    if (!Controller)
        return;

    const auto PerceptionComponent = DS_Utils::GetComponentByUserClass<UDS_AIPerceptionComponent>(Controller);
    if (!PerceptionComponent)
        return;

    AActor *EnemyActor = PerceptionComponent->GetClosestEnemy();
    if (!EnemyActor)
        return;

    ViewLocation = GetMuzzleSocketLocation();
    ViewRotation = (EnemyActor->GetActorLocation() - ViewLocation).GetSafeNormal();
    TraceEndPoint = ViewLocation + ViewRotation * TraceDistance;

    return;
}

void ADS_BaseWeapon::MakeHit(FHitResult &HResult, const FVector &TraceStartPoint, const FVector &TraceEndPoint)
{
    if (!GetWorld()) return;

    FCollisionQueryParams CollisionParams;
    CollisionParams.bReturnPhysicalMaterial = true;
    CollisionParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HResult, TraceStartPoint, TraceEndPoint, ECollisionChannel::ECC_Visibility, CollisionParams);
};



