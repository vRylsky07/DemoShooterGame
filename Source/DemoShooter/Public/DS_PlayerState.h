// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "DS_PlayerState.generated.h"

/**
 * 
 */
UCLASS()
class DEMOSHOOTER_API ADS_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    void SetTeamID(int32 ID){TeamID = ID;};
    int32 GetTeamID() const {return TeamID;};

	void SetTeamColor(const FLinearColor &Color){TeamColor = Color;};
    FLinearColor GetTeamColor() const{return TeamColor;};

private:
    int32 TeamID;
	FLinearColor TeamColor;
};
