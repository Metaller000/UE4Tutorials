#include "TutorialProject.h"
#include "InteractableActor.h"
#include "MyPlayer.h"

// Задаёт переменые по умолчанию
AInteractableActor::AInteractableActor(){
 	// задаёт этот actor для Tick() каждый кадр.  Можно отключить, если не нужно.
	PrimaryActorTick.bCanEverTick = true;
}

// Вызывается во время старта игры
void AInteractableActor::BeginPlay(){
    Super::BeginPlay();

    // Находит все меши в начале игры
    for (UActorComponent* Mesh : GetComponentsByClass(UMeshComponent::StaticClass())) {
        UMeshComponent* thisMesh = Cast<UMeshComponent>(Mesh);
        if(thisMesh){
            Meshes.Push(thisMesh);
            thisMesh->SetCustomDepthStencilValue((uint8)Color);
        }
    }
}

// Вызывается на каждом кадре
void AInteractableActor::Tick( float DeltaTime ){
	Super::Tick( DeltaTime );
}

void AInteractableActor::OnInteract_Implementation(AActor* Caller){
    AMyPlayer* Player = Cast<AMyPlayer>(Caller);
    if(Player){
        UE_LOG(LogTemp, Warning, TEXT("Выполняет"));
        Destroy();
    }
}

void AInteractableActor::OnBeginFocus(){
    if(bCanInteract){
        for(UMeshComponent* Mesh : Meshes){
            Mesh->SetRenderCustomDepth(true);
        }
    }
}

void AInteractableActor::OnEndFocus(){
    for(UMeshComponent* Mesh : Meshes){
        Mesh->SetRenderCustomDepth(false);
    }
}
