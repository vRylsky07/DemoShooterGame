// DemoShooter. All right reserved.


#include "UI/DS_SpectatorWidget.h"
#include "DS_Utils.h"
#include "Components/DS_RespawnComponent.h"

bool UDS_SpectatorWidget::GetRespawnTime(int32& CountDownTime) const
{
	const auto RespawnComponent = DS_Utils::GetComponentByUserClass<UDS_RespawnComponent>(GetOwningPlayer());
	if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

	CountDownTime = RespawnComponent->GetRespawnCountDown();
	return true;
};