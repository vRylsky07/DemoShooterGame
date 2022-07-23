// DemoShooter. All right reserved.


#include "Animations/DS_AnimNotify.h"

void UDS_AnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
};