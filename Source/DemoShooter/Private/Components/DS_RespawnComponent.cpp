// DemoShooter. All right reserved.

#include "Components/DS_RespawnComponent.h"
#include "DemoShooterModeBase.h"

UDS_RespawnComponent::UDS_RespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDS_RespawnComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UDS_RespawnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UDS_RespawnComponent::Respawn(int32 RespawnTime)
{
	if (!GetWorld()) return;

	RespawnCountDown = RespawnTime;

	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UDS_RespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

bool UDS_RespawnComponent::IsRespawnInProgress() const
{
	return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void UDS_RespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0) 
	{
		if (!GetWorld()) return;

		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

		const auto GameMode = Cast<ADemoShooterModeBase>(GetWorld()->GetAuthGameMode());
		if (!GameMode) return;

		GameMode->RespawnRequest(Cast<AController>(GetOwner()));
	};
}

