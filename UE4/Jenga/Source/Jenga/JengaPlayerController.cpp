// Fill out your copyright notice in the Description page of Project Settings.


#include "JengaPlayerController.h"
#include "HeadMountedDisplayFunctionLibrary.h"

AJengaPlayerController::AJengaPlayerController()
{
    UE_LOG(LogTemp, Warning, TEXT("Loadding JengaPlayerController"));
    bShowMouseCursor = true;
    DefaultMouseCursor = EMouseCursor::Crosshairs;
    
}

void AJengaPlayerController::BeginPlay()
{
    cameraman = Cast<Acameraman>(GetPawn());
    
}

void AJengaPlayerController::PlayerTick(float DeltaTime)
{
    Super::PlayerTick(DeltaTime);
}


void AJengaPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAxis("Turn", this, &AJengaPlayerController::DragMouseX);
    InputComponent->BindAxis("LookUp", this, &AJengaPlayerController::DragMouseY);
    InputComponent->BindAxis("Zoom", this, &AJengaPlayerController::MouseWheel);
    InputComponent->BindAction("Mouse_Right", IE_Pressed, this, &AJengaPlayerController::OnMouseRightPressed);
    InputComponent->BindAction("Mouse_Right", IE_Released, this, &AJengaPlayerController::OnMouseRightReleased);
    InputComponent->BindAction("Mouse_Left", IE_Pressed, this, &AJengaPlayerController::OnMouseLeftPressed);
    InputComponent->BindAction("Mouse_Left", IE_Released, this, &AJengaPlayerController::OnMouseLeftReleased);
}


/*******************************************
 * Mouse Control
 * 
 *******************************************/

void AJengaPlayerController::OnMouseLeftPressed()
{
    // Currently the when the cursor clicked on the wood stick, enter interacte mode automatically.

    switch(controlMode)
    {
        case(FREE_MODE):
        {
            // Detect whether the cursor is touch the wood stick.
            AWoodStick* hitWood = cameraman->GetWoodCursorHit(interactingHitResult);
            if(hitWood != NULL)
            {
                controlMode = INTERACT_MODE;
                // Record the current interacting wood stick.
                interactingWood = hitWood;
                
            }
            break;
        }
    }
}

void AJengaPlayerController::OnMouseLeftReleased()
{
    // If the pressed and released position is the same, then enter the selection mode.
    // Otherwise do nothing
    controlMode = FREE_MODE;

}

void AJengaPlayerController::OnMouseRightPressed()
{
    controlMode = CAMERA_MODE;
}

void AJengaPlayerController::OnMouseRightReleased()
{
    controlMode = FREE_MODE;
}

void AJengaPlayerController::DragMouseX(float Axis)
{
    switch(controlMode)
    {
        case(CAMERA_MODE):
        {
            cameraman->DragCameraX(Axis);
            break;
        }
        case(INTERACT_MODE):
        {
            // Start to interact with the wood
            // Generate a X direction Force which is parallel to the ground and perpendicular to the Normal of the hitResult
            // Normal*Z
            FVector forceDirection = FVector::CrossProduct(interactingHitResult.Normal, FVector(0,0,1));
            forceDirection.Normalize();
            FVector force = forceDirection*Axis*XForceScale;
            interactingWood->VisibleComponent->AddForce(force);
            
        }
    }
    
}

void AJengaPlayerController::DragMouseY(float Axis)
{
    switch(controlMode)
    {
        case(CAMERA_MODE):
        {
            cameraman->DragCameraY(Axis);
            break;
        }
        case(INTERACT_MODE):
        {
            // Start to interact with the wood
            // Generate a X direction Force which is parallel to the ground and perpendicular to the Normal of the hitResult
            // Normal*Z
            FVector forceDirection = interactingHitResult.Normal;
            forceDirection.Normalize();
            FVector force = forceDirection*Axis*(-YForceScale);
            interactingWood->VisibleComponent->AddForce(force);
            
            UE_LOG(LogTemp, Warning, TEXT("Y force: (%f, %f, %f)"), force.X, force.Y, force.Z);
        }
    }
    
}

void AJengaPlayerController::MouseWheel(float Axis)
{
    cameraman->ZoomCamera(Axis);
}

void AJengaPlayerController::MoveCameramanTo(FVector Direction, FRotator Rotation)
{

}

/*******************************************
 * Touch Control
 * 
 *******************************************/



/*******************************************
 * Shared Functions
 * The functions that are shared between both
 * touch and mouse controls.
 *******************************************/

void AJengaPlayerController::SelectWood(AWoodStick* woodStick)
{

}
void AJengaPlayerController::UnSelectWood(AWoodStick* woodStick)
{

}

