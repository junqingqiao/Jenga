// BUGMAN May 21th 2020
// The layer between the behavior of camera and physical controller such as mouse and hand.
#pragma once

#include "CoreMinimal.h"
#include "cameraman.h"
#include "GameFramework/PlayerController.h"
#include "WoodStick.h"
#include "JengaPlayerController.generated.h"


/*************************
FREE_MODE allows free mouse movement.
CAMERA_MODE allows the movement of camera
INTERACT_MODE allows player interacting with the Jenga
**************************/
UENUM(BlueprintType)
	enum ControlMode 
	{ 
		FREE_MODE			UMETA(DisplayName = "FREE_MODE"), 
		CAMERA_MODE			UMETA(DisplayName = "CAMERA_MODE"), 
		SELECTION_MODE		UMETA(DisplayName = "SELECTION"),
		INTERACT_MODE		UMETA(DisplayName = "INTERACT_MODE"), 
	};


/**
 *  This class contains all the functions dealing with the controller
 */
UCLASS()
class JENGA_API AJengaPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:
	AJengaPlayerController();
	
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void OnMouseLeftPressed();
	void OnMouseLeftReleased();

	void OnMouseRightPressed();
	void OnMouseRightReleased();
	
	void DragMouseX(float Axis);
	void DragMouseY(float Axis);
	void MouseWheel(float Axis);

	void MoveCameramanTo(FVector Direction, FRotator Rotation);

	UFUNCTION(BlueprintCallable)
	void SelectWood(AWoodStick* woodStick);

	UFUNCTION(BlueprintCallable)
	void UnSelectWood(AWoodStick* woodStick);


	// Indicate the current mode of the controller.
	// BlueprintReadOnly will generate a "Get" blueprint function
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TEnumAsByte<ControlMode> controlMode = FREE_MODE;

	// The selected electrode. It should be exposed on the blueprint, so that the property of the electorde can be accessed.
	// BlueprintReadWrite will generate both "Get" and "Set" blueprint functions.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AWoodStick* selectedWood;

	// The cameraPawn
	Acameraman* cameraman;

	private:
	AWoodStick* interactingWood;
	

};
