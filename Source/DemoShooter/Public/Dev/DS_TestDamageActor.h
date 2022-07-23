// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SceneComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "DS_TestDamageActor.generated.h"

UCLASS()
class DEMOSHOOTER_API ADS_TestDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADS_TestDamageActor();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USceneComponent * SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Damage1 = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool DoFullDmg = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TSubclassOf<UDamageType> DamageType;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
