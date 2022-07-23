// DemoShooter. All right reserved.


#include "DemoShooterModeBase.h"
#include "UI/DS_HUD.h"
#include "AIController.h"
#include "DS_PlayerState.h"

ADemoShooterModeBase::ADemoShooterModeBase()
{
    DefaultPawnClass = ADemoShooterPlayerCharacter::StaticClass();
    PlayerControllerClass = ADemoShooterPlayerController::StaticClass();
    HUDClass = ADS_HUD::StaticClass();
    PlayerStateClass = ADS_PlayerState::StaticClass();
}

void ADemoShooterModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();
    CurrentRound = 1;
    StartRound();
}

UClass *ADemoShooterModeBase::GetDefaultPawnClassForController_Implementation(AController *InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    };

    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ADemoShooterModeBase::SpawnBots()
{
    if (!GetWorld()) return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto AIControllerSpawned = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(AIControllerSpawned);
    };
}
void ADemoShooterModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameTimeRoundHandle, this, &ADemoShooterModeBase::GameTimerUpdate, 1.0f, true);
}
void ADemoShooterModeBase::GameTimerUpdate()
{
    UE_LOG(LogTemp, Error, TEXT("Time: %i / Round: %i : %i"), RoundCountDown, CurrentRound, GameData.RoundsNum)

    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameTimeRoundHandle);
        if (CurrentRound + 1 <= GameData.RoundsNum)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("GAME OVER!"))
        };
    };
}
void ADemoShooterModeBase::ResetPlayers()
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    };
}

void ADemoShooterModeBase::ResetOnePlayer(AController *Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    };
    RestartPlayer(Controller);
}
void ADemoShooterModeBase::CreateTeamsInfo()
{
    if (!GetWorld())
        return;

    int32 TeamID = 1;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<ADS_PlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;
        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        SetTeamColor(Controller);

        TeamID = TeamID == 1 ? 2 : 1;
    };
}
FLinearColor ADemoShooterModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    };
    UE_LOG(LogTemp, Warning, TEXT("No TeamColor set for ID = %i"), TeamID)
    return GameData.DefaultTeamColor;
}
void ADemoShooterModeBase::SetTeamColor(AController *Controller)
{
    if (!Controller)
        return;

    const auto Character = Cast<ADemoShooterPlayerCharacter>(Controller->GetPawn());
    if (!Character)
        return;

    const auto PlayerState = Cast<ADS_PlayerState>(Controller->PlayerState);
    if (!PlayerState)
        return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
};
