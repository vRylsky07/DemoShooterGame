// DemoShooter. All right reserved.


#include "DS_PlayerState.h"

void ADS_PlayerState::LogInfo()
{
	UE_LOG(LogTemp, Display, TEXT("TeamID = %i, KillsNum = %i, DeathsNum = %i"), TeamID, KillsNum, DeathsNum);
}
