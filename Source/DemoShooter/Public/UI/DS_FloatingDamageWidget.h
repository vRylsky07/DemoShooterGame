// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DS_FloatingDamageWidget.generated.h"

UCLASS()
class DEMOSHOOTER_API UDS_FloatingDamageWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetOwnerActor(AActor *NewOwner){OwnerActor = NewOwner;};
    void SetDamageTaken(float Damage){DamageTaken = FMath::CeilToFloat(Damage);};
    FVector2D GetClampedScale(float CurrentDistance);

    UFUNCTION(BlueprintCallable)
    float GetDamageTaken() const {return DamageTaken;};

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Required UI Data")
    AActor *OwnerActor;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Required UI Data")
    FVector2D ScaleValue = FVector2D(0.3f, 1.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Required UI Data")
    FVector2D ScaleDistance = FVector2D(3500.0f, 0.0f);

    float DamageTaken = 0;
};
