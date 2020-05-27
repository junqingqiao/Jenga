// BUGMAN Apr 19
// This class is an actor component for the woodstick objects.
// When the mouse is on the wood stick an event will be generated.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WoodStickComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class JENGA_API UWoodStickComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWoodStickComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
