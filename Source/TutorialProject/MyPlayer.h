// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

UCLASS()
class TUTORIALPROJECT_API AMyPlayer : public ACharacter {
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

    //input
    void MoveForward(float val);
    void MoveRight(float val);
    void LookYaw(float val);
    void LookPitch(float val);
    void Use();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
private:

};
