// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Player/DemoShooterPlayerCharacter.h"
#include "Player/DemoShooterPlayerController.h"
#include "DS_CoreTypes.h"
#include "DS_PlayerState.h"
#include "DemoShooterModeBase.generated.h"

class AAIController;

UCLASS()
class DEMOSHOOTER_API ADemoShooterModeBase : public AGameModeBase
{
    GENERATED_BODY()

public:

    ADemoShooterModeBase();

    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

    void Killed(AController* KillerController, AController* VictimController);
    void LogPlayersInfo();

    FGameData GetGameData() const { return GameData; };
    int32 GetCurrentRound() const { return CurrentRound; };
    int32 GetRoundCountDown() const { return RoundCountDown; };

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FGameData GameData;

private:
    int32 CurrentRound = 0;
    int32 RoundCountDown = 0;
    FTimerHandle GameTimeRoundHandle;

    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();
    void ResetPlayers();
    void ResetOnePlayer(AController * Controller);
    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;
    void SetTeamColor(AController *Controller);


};
