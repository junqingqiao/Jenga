// Fill out your copyright notice in the Description page of Project Settings.


#include "WoodStickComponent.h"


// Sets default values for this component's properties
UWoodStickComponent::UWoodStickComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWoodStickComponent::BeginPlay()
{
	Super::BeginPlay();

	// ..JengaPlayerController.
	
}


// Called every frame
void UWoodStickComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Force the wood to run physics simulation by adding force on each of them
}

