#pragma once

#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

UCLASS()
class TUTORIALPROJECT_API AMyPlayer : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

    // инпуты
    void MoveForward(float val);
    void MoveRight(float val);
    void LookYaw(float val);
    void LookPitch(float val);
    void Use();
    void StartRun();
    void StopRun();

    class AInteractableActor* FindFocusedActor();
    void HandleHighLight();
    void OnDeath();
    void Heal(float Amount);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
    virtual float TakeDamage (float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
    UCameraComponent* PlayerCamera;
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess="true"))
    USpringArmComponent* CameraBoom;

private:
    UPROPERTY(EditDefaultsOnly)
    float InteractionDistence = 300.f;
    UPROPERTY(EditDefaultsOnly)
    float MaxHealthPoints = 100.f;
    UPROPERTY(EditDefaultsOnly)
    float WalkSpeed = 400.f;
    UPROPERTY(EditDefaultsOnly)
    float RunSpeed = 800.f;


    UPROPERTY(BlueprintReadWrite, meta = (AllowPrivateAccess="true"), Category = Health)
    float HealthPoints;

    uint32 bIsRunning : 1;

    AInteractableActor* FocusedActor;
    FCollisionQueryParams TraceParams;
};
