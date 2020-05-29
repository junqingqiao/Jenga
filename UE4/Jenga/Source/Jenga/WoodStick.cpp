// Fill out your copyright notice in the Description page of Project Settings.


#include "WoodStick.h"

// Sets default values
AWoodStick::AWoodStick()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisiableMesh"));
	VisibleComponent->SetupAttachment(RootComponent);
	VisibleComponent->SetSimulatePhysics(false);
	
	
}

// Called when the game starts or when spawned
void AWoodStick::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWoodStick::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->VisibleComponent->AddForce(FVector(0,0,0.1));
}

