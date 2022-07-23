// DemoShooter. All right reserved.


#include "UI/DS_HUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void ADS_HUD::DrawHUD()
{
    //DrawCrosshair();


};

void ADS_HUD::BeginPlay()
{
    Super::BeginPlay();
    auto PlayerHUDWidgetTempRef = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidget);
    if (PlayerHUDWidgetTempRef) PlayerHUDWidgetTempRef->AddToViewport();
}

void ADS_HUD::DrawCrosshair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);
    const float HalfLineSize = 10.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness );
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}
