#include "TutorialProject.h"
#include "MyPlayer.h"
#include "InteractableActor.h"


// Задаёт переменные по умалчанию
AMyPlayer::AMyPlayer() {
    // Задаём этот параметр для вызова Tick() на каждом кадре.
    // Мажно выключить для увелечения производительности, если параметр не нужен.
	PrimaryActorTick.bCanEverTick = true;

    TraceParams = FCollisionQueryParams(FName(TEXT("TraceParams")), false, this);
    TraceParams.bTraceComplex = false;
    TraceParams.bTraceAsyncScene = false;
    TraceParams.bReturnPhysicalMaterial = false;

    PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PlayerCamera"));
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->AttachTo(RootComponent);
    PlayerCamera->AttachTo(CameraBoom);
}

// Вызывается при старте игры или появлении персонажа
void AMyPlayer::BeginPlay() {
	Super::BeginPlay();

    HealthPoints = MaxHealthPoints;
}

// Вызывается на каждом кадре
void AMyPlayer::Tick( float DeltaTime ) {
	Super::Tick( DeltaTime );

    if(Controller && Controller->IsLocalController()){
        HandleHighLight();
        GEngine->AddOnScreenDebugMessage(0, DeltaTime, FColor::Red, FString::Printf(TEXT("HP: %f"), HealthPoints));
    }
}

// Вызывается при создании функциональности для input
void AMyPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
	Super::SetupPlayerInputComponent(InputComponent);

    InputComponent->BindAxis("MoveForward", this, &AMyPlayer::MoveForward);
    InputComponent->BindAxis("MoveRight", this, &AMyPlayer::MoveRight);
    InputComponent->BindAxis("LookYaw", this, &AMyPlayer::LookYaw);
    InputComponent->BindAxis("LookPitch", this, &AMyPlayer::LookPitch);
    InputComponent->BindAction("Use", IE_Pressed, this, &AMyPlayer::Use);
    InputComponent->BindAction("Run", IE_Pressed, this, &AMyPlayer::StartRun);
    InputComponent->BindAction("Run", IE_Released, this, &AMyPlayer::StopRun);
}


void AMyPlayer::MoveForward(float val){
    FRotator Rotation(0, GetActorRotation().Yaw, 0);
    FVector Forward(1, 0, 0);  //= FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
    AddMovementInput(Forward, val);
}

void AMyPlayer::MoveRight(float val){
    FRotator Rotation(0, GetActorRotation().Yaw, 0);
    FVector Right(0, 1, 0);  //= FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
    AddMovementInput(Right, val);
}

void AMyPlayer::LookYaw(float val){
    AddControllerYawInput(val);
}

void AMyPlayer::LookPitch(float val){
    AddControllerPitchInput(val);
}

// Действия при использовании
void AMyPlayer::Use(){
    AInteractableActor* Interactable = FindFocusedActor();
    if(Interactable){
        Interactable->OnInteract(this);
    }
}

void AMyPlayer::StartRun(){
    bIsRunning = true;
    GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

void AMyPlayer::StopRun(){
    bIsRunning = false;
    GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

AInteractableActor* AMyPlayer::FindFocusedActor(){
    if(!Controller){
        return nullptr;
    }

    FVector Location;
    FRotator Rotation;
    FHitResult Hit(ForceInit);
    Controller->GetPlayerViewPoint(Location, Rotation);

    FVector Start = Location;
    FVector End = Start + (Rotation.Vector() * InteractionDistence);

    GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Camera, TraceParams);

    if(Hit.bBlockingHit){
        AInteractableActor* MyCastActor = Cast<AInteractableActor>(Hit.GetActor());
        if(MyCastActor){
            return MyCastActor;
        }
    }
    return nullptr;
}

void AMyPlayer::HandleHighLight(){
    AInteractableActor* NewHighLight = FindFocusedActor();

    if(NewHighLight){
        if(NewHighLight != FocusedActor){
            if (FocusedActor) FocusedActor->OnEndFocus();
            NewHighLight->OnBeginFocus();
            FocusedActor = NewHighLight;
        }
    }else{
        if (FocusedActor) FocusedActor->OnEndFocus();
        FocusedActor = nullptr;
    }
}

// Действия при повреждениях
float AMyPlayer::TakeDamage (float DamageAmount, struct FDamageEvent const & DamageEvent, class AController* EventInstigator, AActor* DamageCauser){
    float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    HealthPoints = HealthPoints - ActualDamage;
    if(HealthPoints <= 0){
        OnDeath();
    }
    return ActualDamage;
}

// Действие(я) при смерти
void AMyPlayer::OnDeath(){
    UE_LOG(LogTemp, Warning, TEXT("Ты умер!"));
    Destroy();
}

// Действие при лечении
void AMyPlayer::Heal(float Amount){
    if (Amount > 0){
        HealthPoints = HealthPoints + Amount;
    }
}
