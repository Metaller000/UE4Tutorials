#pragma once

#include "GameFramework/Actor.h"
#include "TutorialProject.h"
#include "InteractableActor.generated.h"

UCLASS()
class TUTORIALPROJECT_API AInteractableActor : public AActor
{
	GENERATED_BODY()

public:
	// Утанавливает значения по умолчанию для свойств этого actor
	AInteractableActor();

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category=Interaction)
    void OnInteract(AActor* Caller);
    virtual void OnInteract_Implementation(AActor* Caller);

    void OnBeginFocus();
    void OnEndFocus();
	// Вызывается во время старта игры
	virtual void BeginPlay() override;
	// Вызывается на каждом кадре
	virtual void Tick( float DeltaSeconds ) override;

private:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Interaction, meta = (AllowPrivateAccess = "true"))
    uint32 bCanInteract : 1;
    TArray<class UMeshComponent*> Meshes;
    UPROPERTY(EditDefaultsOnly)
    EStencilColor Color = EStencilColor::SC_Blue;
};
