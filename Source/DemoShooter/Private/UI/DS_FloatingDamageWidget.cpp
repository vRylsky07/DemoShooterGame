// DemoShooter. All right reserved.


#include "UI/DS_FloatingDamageWidget.h"

FVector2D UDS_FloatingDamageWidget::GetClampedScale(float CurrentDistance)
{
    float FinalScale = FMath::GetMappedRangeValueClamped(ScaleDistance, ScaleValue, CurrentDistance);
    return FVector2D(FinalScale, FinalScale);
}

