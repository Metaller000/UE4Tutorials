// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableActor.h"
#include "MyHealthPickup.generated.h"

/**
 *
 */
UCLASS()
class TUTORIALPROJECT_API AMyHealthPickup : public AInteractableActor
{
	GENERATED_BODY()
public:
    virtual void OnInteract_Implementation(AActor* Caller) override;

private:
    UPROPERTY(EditDefaultsOnly)
    float HealAmount = 25.f;

};
