// DemoShooter. All right reserved.


#include "DemoShooterModeBase.h"
#include "UI/DS_HUD.h"
#include "UI/DS_PlayerHUD.h"
#include "AIController.h"
#include "Components/DS_RespawnComponent.h"
#include "DS_Utils.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
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

void ADemoShooterModeBase::RestartPlayer(AController* NewPlayer)
{
    if (NewPlayer == nullptr || NewPlayer->IsPendingKillPending())
    {
        return;
    }

    if (!GetWorld()) return;
    TArray<AActor*> PS_Array;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PS_Array);
    int32 RandomPS = 0;
    
    if (PS_Array.Num() > 0) {
        RandomPS = FMath::RandRange(0, PS_Array.Num() - 1);
        RestartPlayerAtPlayerStart(NewPlayer, PS_Array[RandomPS]);
    }
    else {
        if (GEngine)
            GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Player Start was not found!"));
    };

}

void ADemoShooterModeBase::Killed(AController* KillerController, AController* VictimController)
{
    const auto KillerPlayerState = KillerController ? Cast<ADS_PlayerState>(KillerController->PlayerState) : nullptr;
    const auto VictimPlayerState = VictimController ? Cast<ADS_PlayerState>(VictimController->PlayerState) : nullptr;

    if (KillerPlayerState) 
    {
        KillerPlayerState->AddKill();
    };

    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    };

    StartRespawn(VictimController);
}

void ADemoShooterModeBase::LogPlayersInfo()
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<ADS_PlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;

        PlayerState->LogInfo();
    };
}

void ADemoShooterModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}

void ADemoShooterModeBase::GameOver()
{
    UE_LOG(LogTemp, Error, TEXT("GAME OVER!"))
    LogPlayersInfo();

    if (!GetWorld()) return;

    for (auto Pawn : TActorRange<APawn>(GetWorld())) 
    {
        if (Pawn) Pawn->TurnOff();
        Pawn->DisableInput(nullptr);
    };
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
            GameOver();
            OnGameOverEvent();
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
    SetTeamColor(Controller);
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
}
void ADemoShooterModeBase::StartRespawn(AController* Controller)
{
    const auto RespawnAvailable = RoundCountDown > MinTimeForRespawn + +GameData.RoundRespawnTime;
    if (!RespawnAvailable) return;

    const auto RespawnComponent = DS_Utils::GetComponentByUserClass<UDS_RespawnComponent>(Controller);
    if (!RespawnComponent) return;

    RespawnComponent->Respawn(GameData.RoundRespawnTime);
}
;
