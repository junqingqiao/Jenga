// Fill out your copyright notice in the Description page of Project Settings.


#include "cameraman.h"
#include "Engine/World.h"
#include "HeadMountedDisplayFunctionLibrary.h"

// Sets default values
Acameraman::Acameraman()
{
	// Setup the RootComponent
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	VisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisiableMesh"));
	VisibleComponent->SetupAttachment(RootComponent);
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Because I'm using the pawn class there is a controller embedded here.
	//controller = GetWorld()->GetFirstPlayerController();

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	// So root component is a part of actor. 
	// To move the camera focusing point I can change the position of this pawn.
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = CameraArmLenght;
	// CameraBoom->bUsePawnControlRotation = true;
	// Setup the camera
	FocusCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FocusCamera"));
	FocusCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FocusCamera->bUsePawnControlRotation = true;

	// Setup the cursor
	CursorToWorld = CreateDefaultSubobject<UDecalComponent>("CursorToWorld");
	CursorToWorld->SetupAttachment(RootComponent);

	CursorToWorld->DecalSize = FVector(16.0f, 32.0f, 32.0f);
	CursorToWorld->SetRelativeRotation(FRotator(90.f, 0.f, 0.f).Quaternion());

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}	

// Called when the game starts or when spawned
void Acameraman::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void Acameraman::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Mouse Control
	if (CursorToWorld != nullptr)
	{
		if(APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			FHitResult TraceHitResult;
			PC->GetHitResultUnderCursor(ECC_Visibility, true, TraceHitResult);
			FVector CursorFV = TraceHitResult.ImpactNormal;
			FRotator CursorR = CursorFV.Rotation();
			CursorToWorld->SetWorldLocation(TraceHitResult.Location);
			CursorToWorld->SetWorldRotation(CursorR);

			// Move the camera to the hit point
			// this->SetActorLocation(TraceHitResult.Location);
			// this->AddMovementInput(TraceHitResult.Location, 1);
			if(TraceHitResult.GetActor())
			{
				if(TraceHitResult.GetActor()->IsRootComponentMovable())
				{
					UStaticMeshComponent* MeshRootComp = Cast<UStaticMeshComponent>(TraceHitResult.GetActor()->GetRootComponent());
					MeshRootComp->AddForce(FocusCamera->GetForwardVector()*PushForce);
				}
			}
		}
	}
}

void Acameraman::DragCameraX(float axis)
{
	FRotator deltaRotation = FRotator::ZeroRotator;
	deltaRotation.Yaw = axis;
	CameraBoom->AddLocalRotation(deltaRotation);
}

void Acameraman::DragCameraY(float axis)
{
	FVector deltaLocation = FVector::ZeroVector;
	deltaLocation.Z = -axis;
	this->AddActorWorldOffset(deltaLocation);
}

// Zoom in and out the camera
void Acameraman::ZoomCamera(float axis)
{
	FVector deltaLocation = FVector::ZeroVector;
	this->CameraBoom->TargetArmLength -= axis;
}

bool Acameraman::GetCursorHitOnWood(FHitResult &hitResult)
{
	bool result = false;
	if (CursorToWorld != nullptr)
	{
		if(APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			// The ECC_GameTraceChannel1 is the collision channel for wood.
			result = PC->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, true, hitResult);
			if(result)
			{
				// UE_LOG(LogTemp, Warning, TEXT("Get Hit on Muscle"));
			}
		}
	}
	return (result);
}

AWoodStick* Acameraman::GetWoodCursorHit()
{
	// This function returns the wood which cursor hit.
	// If there is no wood is hit return null
	AWoodStick* result = NULL;
	FHitResult hitResult;
	if (CursorToWorld != nullptr)
	{
		if(APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			// EEC_GameTraceChannel2 is the collision channel of electrodes.
			if(PC->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, true, hitResult))
			{
				result = Cast<AWoodStick>(hitResult.GetActor());
				
			}
		}
	}
	return(result);
}

AWoodStick* Acameraman::GetWoodCursorHit(FHitResult &hitResult)
{
	// If no wood is hit return NULL.

	AWoodStick* result = NULL;
	if (CursorToWorld != nullptr)
	{
		if(APlayerController* PC = Cast<APlayerController>(GetController()))
		{
			// EEC_GameTraceChannel2 is the collision channel of electrodes.
			if(PC->GetHitResultUnderCursor(ECollisionChannel::ECC_GameTraceChannel1, true, hitResult))
			{
				result = Cast<AWoodStick>(hitResult.GetActor());
			}
		}
	}
	return(result);
}

