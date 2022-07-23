// DemoShooter. All right reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DemoShooterPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UHealthComponentPointer;
class UDSHealthComponent;
class UTextRenderComponent;
class UAnimMontage;
class UDS_WeaponComponent;

UCLASS()
class DEMOSHOOTER_API ADemoShooterPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
  ADemoShooterPlayerCharacter();
  ADemoShooterPlayerCharacter(const FObjectInitializer &ObjectInit);

protected:

	virtual void BeginPlay() override;


  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UCameraComponent *CameraComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  USpringArmComponent *SpringArmComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UDSHealthComponent *HealthComponentPointer;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UTextRenderComponent *HealthTextComponent;

  UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
  UDS_WeaponComponent *WeaponComponent;

  UPROPERTY(EditDefaultsOnly, Category = "Animations")
  UAnimMontage *DeathAnimMontagePtr;






public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void OnDeath();

	void MoveForward(float Amount);
    void MoveRight(float Amount);
    void OnStartRunning();
    void OnStopRunning();
    void SetPlayerColor(const FLinearColor & Color);


    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float VelocityAngle() const;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	float FallSpeed = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 3000.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    FVector2D LandedDamage = FVector2D(300.0f, 5000.0f);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage")
    float DeathSpanTime = 5.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Material")
    FName MaterialColorName = "Paint Color";

	private:
    bool WantsToRun = false;
    bool IsMovingForward = false;

    void OnHealthChanged(float Health);
    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);


};

