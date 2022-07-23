// DemoShooter. All right reserved.

#include "Weapon/Components/DSWeaponFXComponent.h"

UDSWeaponFXComponent::UDSWeaponFXComponent()
{
 	PrimaryComponentTick.bCanEverTick = false;

}


void UDSWeaponFXComponent::PlayImpactFX(const FHitResult &HitResult, FVector & ScaleValue)
{
    auto ImpactData = DefaultImpactData;
    if (HitResult.PhysMaterial.IsValid())
    {
        const auto NewPhysMat = HitResult.PhysMaterial.Get();
        if (ImpactDataMap.Contains(NewPhysMat))
        {
            ImpactData = ImpactDataMap[NewPhysMat];
        };
    };

    //Spawn Niagara Effect on shoot
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),//
        ImpactData.NiagaraEffect, //
        HitResult.ImpactPoint, //
        HitResult.ImpactNormal.Rotation(), //
        ScaleValue);

    //Spawn Decal on shoot
    const auto DecalData = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), //
        ImpactData.DecalData.Material, //
        ImpactData.DecalData.Size,
        HitResult.ImpactPoint,
        HitResult.ImpactNormal.Rotation());
    if (DecalData)
        DecalData->SetFadeScreenSize(0.00001f);
    if (DecalData)
        DecalData->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
}

void UDSWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();

}


