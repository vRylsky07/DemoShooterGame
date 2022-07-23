// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "DS_AnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent *);

UCLASS()
class DEMOSHOOTER_API UDS_AnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	
	public:
		FOnNotifiedSignature OnNotified;
		virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;
};
