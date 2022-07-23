// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "DS_BasePickup.generated.h"

UCLASS()
class DEMOSHOOTER_API ADS_BasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ADS_BasePickup();

	UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent *CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 15.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    bool CanTakeProperty = true;

	virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

    FTimerHandle RespawnTimer;

	bool CanBeTaken() const;
	void PickupWasTaken();
    void Respawn();
    virtual void AddSupplies(APawn *PlayerPawn){};


protected:

	virtual void BeginPlay() override;
};
