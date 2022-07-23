// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon/Components/DSWeaponFXComponent.h"
#include "DS_Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class DEMOSHOOTER_API ADS_Projectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ADS_Projectile();

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
    USphereComponent *CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
    UProjectileMovementComponent *MovementComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    float Damage = 500.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    bool DoFullDamage = true;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    float ProjectileLifeTime = 5.0f;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UDSWeaponFXComponent *WeaponFXComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "VFX")
    FVector FXScale = {4.0f, 4.0f, 4.0f};

	void SetShotDirection(const FVector &Direction)
    {
        ShotDirection = Direction;
    };

	AController *GetController() const;

	UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit);

protected:
	virtual void BeginPlay() override;

private:
    FVector ShotDirection;
};
