// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DS_PlayerState.generated.h"

UCLASS()
class DEMOSHOOTER_API ADS_PlayerState : public APlayerState
{

    GENERATED_BODY()

public:
    void SetTeamID(int32 ID) { TeamID = ID; };

    UFUNCTION(BlueprintCallable)
    int32 GetTeamID() const { return TeamID; };

    void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; };
    FLinearColor GetTeamColor() const { return TeamColor; };

    void AddKill() { ++KillsNum; };
    int32 GetKills() const { return KillsNum; };

    void AddDeath() { ++DeathsNum; };
    int32 GetDeaths() const {return DeathsNum;};

    void LogInfo();

private:
    int32 TeamID;
	FLinearColor TeamColor;

    int32 KillsNum = 0;
    int32 DeathsNum = 0;

};
