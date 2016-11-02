// Fill out your copyright notice in the Description page of Project Settings.

#include "TutorialProject.h"
#include "IntractibeActor.h"


// Sets default values
AIntractibeActor::AIntractibeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AIntractibeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AIntractibeActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

