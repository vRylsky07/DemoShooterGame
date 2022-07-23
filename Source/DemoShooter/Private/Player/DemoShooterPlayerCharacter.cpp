// DemoShooter. All right reserved.


#include "Player/DemoShooterPlayerCharacter.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/DSHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/DSCharacterMovementComponent.h"
#include "Weapon/DS_BaseWeapon.h"
#include "Components/DS_WeaponComponent.h"
#include "GameFramework/Controller.h"
#include "Components/CapsuleComponent.h"


ADemoShooterPlayerCharacter::ADemoShooterPlayerCharacter(){
};


ADemoShooterPlayerCharacter::ADemoShooterPlayerCharacter(const FObjectInitializer &ObjectInit)
    : Super(ObjectInit.SetDefaultSubobjectClass <UDSCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = false;
    SpringArmComponent->TargetArmLength = 130.0f;
    SpringArmComponent->SocketOffset = FVector(0.0f, 69.0f, 69.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponentPointer = CreateDefaultSubobject<UDSHealthComponent>("HealthComponent");

    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());

    WeaponComponent = CreateDefaultSubobject<UDS_WeaponComponent>("WeaponComponent");

    LandedDelegate.AddDynamic(this, &ADemoShooterPlayerCharacter::OnGroundLanded);
    
}


void ADemoShooterPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
    check(HealthComponentPointer);
    check(HealthTextComponent);
    check(DeathAnimMontagePtr);
    check(WeaponComponent);
    check(GetMesh());

    HealthComponentPointer->OnDeath.AddUObject(this, &ADemoShooterPlayerCharacter::OnDeath);
    HealthComponentPointer->OnHealthChanged.AddUObject(this, &ADemoShooterPlayerCharacter::OnHealthChanged);

    OnHealthChanged(HealthComponentPointer->GetHealth());

}


void ADemoShooterPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADemoShooterPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent);
    InputComponent->BindAxis("MoveForward", this, &ADemoShooterPlayerCharacter::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &ADemoShooterPlayerCharacter::MoveRight);
    InputComponent->BindAxis("LookUp", this, &ADemoShooterPlayerCharacter::AddControllerPitchInput);
    InputComponent->BindAxis("TurnAround", this, &ADemoShooterPlayerCharacter::AddControllerYawInput);
    InputComponent->BindAction("Jump", IE_Pressed, this, &ADemoShooterPlayerCharacter::Jump);
    InputComponent->BindAction("Run", IE_Pressed, this, &ADemoShooterPlayerCharacter::OnStartRunning);
    InputComponent->BindAction("Run", IE_Released, this, &ADemoShooterPlayerCharacter::OnStopRunning);
    InputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UDS_WeaponComponent::StartFire);
    InputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UDS_WeaponComponent::StopFire);
    InputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UDS_WeaponComponent::NextWeapon);
    InputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UDS_WeaponComponent::Reload);
}

void ADemoShooterPlayerCharacter::MoveForward(float Amount)
{
    if (Amount == 0.0f)return;
    IsMovingForward = Amount > 0.0f;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void ADemoShooterPlayerCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f)return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void ADemoShooterPlayerCharacter::OnStartRunning()
{
    WantsToRun = true;
}

void ADemoShooterPlayerCharacter::OnStopRunning()
{
    WantsToRun = false;
}

void ADemoShooterPlayerCharacter::SetPlayerColor(const FLinearColor &Color)
{
    const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInst)
        return;

    MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}

bool ADemoShooterPlayerCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}

float ADemoShooterPlayerCharacter::VelocityAngle() const
{
    if (GetVelocity().IsZero()) return 0.0f;
    const FVector VelocityVector = GetVelocity().GetSafeNormal();
    const float AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityVector));
    const FVector CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityVector);
    const float Degrees = FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ADemoShooterPlayerCharacter::OnDeath()
{
    auto IsMoving = GetVelocity();
    PlayAnimMontage(DeathAnimMontagePtr);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(DeathSpanTime);

    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    };

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    WeaponComponent->StopFire();

    if (IsMoving != FVector::ZeroVector)
    {
        GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        GetMesh()->SetSimulatePhysics(true);
    };
}

void ADemoShooterPlayerCharacter::OnHealthChanged(float Health)
{
    HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

void ADemoShooterPlayerCharacter::OnGroundLanded(const FHitResult &Hit)
{
    FallSpeed = -GetCharacterMovement()->Velocity.Z;

    if (FallSpeed < LandedDamageVelocity.X)
        return;

    const auto FinalFallDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallSpeed);
    TakeDamage(FinalFallDamage, FDamageEvent{}, nullptr, nullptr);
}




