// DemoShooter. All right reserved.

#include "Weapon/DS_Projectile.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

ADS_Projectile::ADS_Projectile()
{
    PrimaryActorTick.bCanEverTick = false;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("Collision Component");
    CollisionComponent->InitSphereRadius(25.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ADS_Projectile::OnProjectileHit);
    CollisionComponent->bReturnMaterialOnMove = true;

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    SetRootComponent(CollisionComponent);
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;

    WeaponFXComponent = CreateDefaultSubobject<UDSWeaponFXComponent>("WeaponFXComponent");

}



void ADS_Projectile::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponFXComponent);
    check(MovementComponent);
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    SetLifeSpan(ProjectileLifeTime);
}

void ADS_Projectile::OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                                     UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    if (GetWorld())
    {
        MovementComponent->StopMovementImmediately();

        UGameplayStatics::ApplyRadialDamage(GetWorld(),         //
                                            Damage,             //
                                            GetActorLocation(), //
                                            DamageRadius,       //
                                            UDamageType::StaticClass(), //
                                            {},                 //
                                            this,               //
                                            GetController(),            //
                                            DoFullDamage);
                                            WeaponFXComponent->PlayImpactFX(Hit, FXScale);
        //DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Yellow, false, 5.0f, {}, 1.0f);
        Destroy();
    };
};

AController *ADS_Projectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
};