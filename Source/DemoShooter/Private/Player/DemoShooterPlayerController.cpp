// DemoShooter. All right reserved.


#include "Player/DemoShooterPlayerController.h"



ADemoShooterPlayerController::ADemoShooterPlayerController() 
{
	RespawnComponent = CreateDefaultSubobject<UDS_RespawnComponent>("DS_RespawnComponent");
};