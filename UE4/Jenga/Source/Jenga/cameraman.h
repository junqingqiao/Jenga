// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "WoodStick.h"

#include "cameraman.generated.h"



UCLASS()
class JENGA_API Acameraman : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	Acameraman();
	
	
	/* All accessable parameters*/
	// Camera
	UPROPERTY(VisibleAnywhere, Category = Camera)
		UCameraComponent* FocusCamera;

	UPROPERTY(VisibleAnywhere)
		USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
		float CameraArmLenght = 30.0f;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* VisibleComponent;

	UPROPERTY(VisibleAnywhere)
		class UDecalComponent* CursorToWorld;
	
	/* Settings */

	UPROPERTY(VisibleAnywhere)
		float MaxFov = 100.0f;

	UPROPERTY(VisibleAnywhere)
		float MinFov = 10.0f;

	UPROPERTY(EditAnywhere)
		float PushForce = 1000.0f;

	// Functions to response for mouse movement.
	void DragCameraX(float Axis);
	void DragCameraY(float Axis);
	void ZoomCamera(float Axis);

	// Helper functions

	void focusToObject();
	bool GetCursorHitOnWood(FHitResult &hitResult);
	AWoodStick* GetWoodCursorHit();
	AWoodStick* GetWoodCursorHit(FHitResult &hitResult);
	//void MoveWood();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
