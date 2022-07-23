// DemoShooter. All right reserved.


#include "Pickup/DS_BasePickup.h"


ADS_BasePickup::ADS_BasePickup()
{
	PrimaryActorTick.bCanEverTick = false;
    CollisionComponent = CreateDefaultSubobject<USphereComponent>("Collision Component");
    CollisionComponent->InitSphereRadius(25.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}


void ADS_BasePickup::BeginPlay()
{
	Super::BeginPlay();
    check(CollisionComponent);
	
}


void ADS_BasePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    PickupWasTaken();
    const auto Pawn = Cast<APawn>(OtherActor);
    
    if (!Pawn)
        return;
    AddSupplies(Pawn);

}

bool ADS_BasePickup::CanBeTaken() const
{
    return !GetWorldTimerManager().IsTimerActive(RespawnTimer);
}

void ADS_BasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);
    GetWorldTimerManager().SetTimer(RespawnTimer, this, &ADS_BasePickup::Respawn, RespawnTime);
}

void ADS_BasePickup::Respawn()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
}

