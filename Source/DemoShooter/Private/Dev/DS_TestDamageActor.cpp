// DemoShooter. All right reserved.


#include "Dev/DS_TestDamageActor.h"

// Sets default values
ADS_TestDamageActor::ADS_TestDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve per formance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ADS_TestDamageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADS_TestDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);
    UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage1, GetActorLocation(), Radius, DamageType, {}, this, nullptr, DoFullDmg);
}
