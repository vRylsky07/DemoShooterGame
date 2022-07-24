// DemoShooter. All right reserved.


#include "Components/DSHealthComponent.h"

UDSHealthComponent::UDSHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UDSHealthComponent::DamageHandler(AActor *ActorPtr1, float Dmg1, const class UDamageType *DamageType1,
                                       class AController * InstigatedBy, AActor *ActorEnemy1)
{
    if (Health <= 0 || IsDead() || !GetWorld())
        return;

    DS_Utils::PlayCameraShake(GetOwner(), IsDead(), CameraShake);
    GetWorld()->GetTimerManager().ClearTimer(AutoHealTimer);
    SetHealth(Health - Dmg1);
    OnHealthChanged.Broadcast(Health);
    IncreaseHealInTime = 0.0f;

    if (IsDead()) {
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    };

    if (AutoHeal && !IsDead())
        GetWorld()->GetTimerManager().SetTimer(AutoHealTimer, this, &UDSHealthComponent::AutoHealFunc, HealUpdate, true, HealDelay);
    ReportDamageEvent(Dmg1, InstigatedBy);
    SpawnDamageWidget(Dmg1, InstigatedBy);
}

void UDSHealthComponent::SpawnDamageWidget(float DamageTaken, AController *InstigatedBy)
{
    if (!InstigatedBy || !InstigatedBy->IsPlayerController())
        return;

    if(!GetOwner()) return;

    const auto Owner = Cast<APawn>(GetOwner());

    if (!Owner)
        return;

    const auto Controller = Owner->GetController();
    if (!Controller)
        return;

    if (!GetWorld())
        return;

    if (!DamageTakenWidget)
        return;

    const auto Widget = CreateWidget<UUserWidget>(GetWorld(), DamageTakenWidget);

    if (!Widget)
        return;

    const auto FloatWidget = Cast<UDS_FloatingDamageWidget>(Widget);
    if (!FloatWidget)
        return;

    if (!InstigatedBy->GetPawn())
        return; 

    float ScaleDistance = (Owner->GetActorLocation() - InstigatedBy->GetPawn()->GetActorLocation()).Size();

    FloatWidget->SetOwnerActor(Owner);
    FloatWidget->SetDamageTaken(DamageTaken);
    FloatWidget->AddToViewport();
    FloatWidget->SetRenderScale(FloatWidget->GetClampedScale(ScaleDistance));

    FTimerHandle WidgetDestroyTimer;

    auto WidgetDestroy{[FloatWidget]() {FloatWidget->RemoveFromParent();}};

    GetWorld()->GetTimerManager().SetTimer(
        WidgetDestroyTimer,
        WidgetDestroy,
        2.0f, false,
        -1.0f);
};

void UDSHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    checkf(MaxHealth > 0, TEXT("Max Health less zero"));

    SetHealth(MaxHealth);
    OnHealthChanged.Broadcast(Health);
    BaseIncreaseHealInTime = IncreaseHealInTime;


    AActor *CurrentCharacter = GetOwner();
    check(CurrentCharacter);
    CurrentCharacter->OnTakeAnyDamage.AddDynamic(this, &UDSHealthComponent::DamageHandler);
}

void UDSHealthComponent::Killed(AController* KillerController)
{
    if (!GetWorld()) return;

    const auto GameMode = Cast<ADemoShooterModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return;

    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;

    GameMode->Killed(KillerController, VictimController);

}

void UDSHealthComponent::AutoHealFunc()
{
    SetHealth(Health + (HealValue + IncreaseHealInTime));
    OnHealthChanged.Broadcast(Health);

    if (Health == MaxHealth && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(AutoHealTimer);
    };

    IncreaseHealInTime += BaseIncreaseHealInTime;
}

void UDSHealthComponent::SetHealth(float NewHp){
    IsItDamage = Health > NewHp ? true : false;
    Health = FMath::Clamp(NewHp, 0.0f, MaxHealth);
}

void UDSHealthComponent::ReportDamageEvent(float Damage, AController *InstigatedBy)
{
    if (!InstigatedBy || !GetOwner() || !InstigatedBy->GetPawn())
    {
        return;
    };

    UAISense_Damage::ReportDamageEvent(
        GetWorld(), 
        GetOwner(), 
        InstigatedBy->GetPawn(), 
        Damage,
        InstigatedBy->GetPawn()->GetActorLocation(), 
        GetOwner()->GetActorLocation());
}

