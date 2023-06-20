// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCameraPawn.h"

// Sets default values
ARTSCameraPawn::ARTSCameraPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RTSCameraComponent = CreateDefaultSubobject<URTS_SmoothCameraComponent>(TEXT("RTSCameraComponent"));
	if (!ensure(RTSCameraComponent != nullptr)) {
		return;
	}
	RTSCameraComponent->SetupAttachment(this->RootComponent);
	
}

// Called when the game starts or when spawned
void ARTSCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARTSCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ARTSCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &ARTSCameraPawn::MoveForward);
	PlayerInputComponent->BindAction("MoveBackward", IE_Pressed, this, &ARTSCameraPawn::MoveBackward);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ARTSCameraPawn::MoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ARTSCameraPawn::MoveRight);

	PlayerInputComponent->BindAction("CameraPan", IE_Pressed, this, &ARTSCameraPawn::CameraPanPressed);
	PlayerInputComponent->BindAction("CameraPan", IE_Released, this, &ARTSCameraPawn::CameraPanReleased);

	PlayerInputComponent->BindAxis("MoveForwardBackward", this, &ARTSCameraPawn::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveSideways", this, &ARTSCameraPawn::MoveSideways);

	PlayerInputComponent->BindAxis("CameraKeyboardPan", this, &ARTSCameraPawn::CameraKeyboardPan);
	PlayerInputComponent->BindAxis("CameraKeyboardPitch", this, &ARTSCameraPawn::CameraKeyboardPitch);
	PlayerInputComponent->BindAxis("CameraZoom", this, &ARTSCameraPawn::CameraZoom);
}

void ARTSCameraPawn::MoveForward()
{
	RTSCameraComponent->MoveCameraUpDown(1.0f);
}

void ARTSCameraPawn::MoveBackward()
{
	RTSCameraComponent->MoveCameraUpDown(-1.0f);
}

void ARTSCameraPawn::MoveLeft()
{
	RTSCameraComponent->MoveCameraLeftRight(1.0f);
}

void ARTSCameraPawn::MoveRight()
{
	RTSCameraComponent->MoveCameraLeftRight(-1.0f);
}

void ARTSCameraPawn::MoveForwardBackward(float AxisValue)
{
	RTSCameraComponent->MoveCameraUpDownPerUnit(AxisValue);
}

void ARTSCameraPawn::MoveSideways(float AxisValue)
{
	RTSCameraComponent->MoveCameraLeftRightPerUnit(AxisValue);
}

void ARTSCameraPawn::CameraPanPressed()
{
	RTSCameraComponent->RotateCameraPressed();
}

void ARTSCameraPawn::CameraPanReleased()
{
	RTSCameraComponent->RotateCameraReleased();
}

void ARTSCameraPawn::CameraKeyboardPan(float AxisValue)
{
	RTSCameraComponent->PanCamera(AxisValue);
}

void ARTSCameraPawn::CameraKeyboardPitch(float AxisValue)
{
	RTSCameraComponent->PitchCamera(AxisValue);
}

void ARTSCameraPawn::CameraZoom(float AxisValue)
{
	RTSCameraComponent->ZoomCamera(AxisValue);
}


