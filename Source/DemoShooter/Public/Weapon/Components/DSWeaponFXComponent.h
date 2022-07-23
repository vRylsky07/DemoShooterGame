// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "DS_CoreTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "DSWeaponFXComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEMOSHOOTER_API UDSWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDSWeaponFXComponent();

	void PlayImpactFX(const FHitResult &HitResult, FVector &ScaleValue);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TMap<UPhysicalMaterial *, FImpactData> ImpactDataMap;

	virtual void BeginPlay() override;

		
};
