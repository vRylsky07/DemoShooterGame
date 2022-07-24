// DemoShooter. All right reserved.


#include "UI/DS_GameModeDataWidget.h"

int32 UDS_GameModeDataWidget::GetKillsNum() const 
{
    const auto PlayerState = GetPlayerState();
    return PlayerState ? PlayerState->GetKills() : 0;
};

int32 UDS_GameModeDataWidget::GetCurrentRoundNum() const
{
    const auto GameMode = GetGameMode();
    return GameMode ? GameMode->GetCurrentRound() : 0;
}

int32 UDS_GameModeDataWidget::GetTotalRoundsNum() const
{
    const auto GameMode = GetGameMode();
    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 UDS_GameModeDataWidget::GetRoundsSecondsRemaining() const
{
    const auto GameMode = GetGameMode();
    return GameMode ? GameMode->GetRoundCountDown() : 0;
}

ADemoShooterModeBase* UDS_GameModeDataWidget::GetGameMode() const
{
    return GetWorld() ? Cast<ADemoShooterModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

ADS_PlayerState* UDS_GameModeDataWidget::GetPlayerState() const
{
    return GetOwningPlayer() ? Cast<ADS_PlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
