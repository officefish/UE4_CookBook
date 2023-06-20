// Fill out your copyright notice in the Description page of Project Settings.


#include "RTS_SmoothCameraComponent.h"

// Sets default values for this component's properties
URTS_SmoothCameraComponent::URTS_SmoothCameraComponent()
{
	/* Setup default values for fields*/
	SetupDefaults();

	/* Initialize spring arm */
	SetupSpringArm();

	/* Initialize Camera */
	SetupCamera();
}

void URTS_SmoothCameraComponent::SetupDefaults()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;

	// Set our default values
	CameraSpeed = 1000.0f;
	CameraZoomSpeed = 20.0f;
	CameraZoomPerUnit = 300.0f;

	CameraPanPerUnit = 3.0f;
	CameraPitchPerUnit = 1.0f;

	CameraMaximumPitch = -85.0f;
	CameraMinimumPitch = -20.0f;

	MinCameraDistance = 500.0f;
	MaxCameraDistance = 2500.0f;

	//CameraScrollThreshold = 20.0f;

	TargetCameraZoomDistance = 1500.0f;
}

void URTS_SmoothCameraComponent::SetupSpringArm()
{
	// Create Camera Spring Arm
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));

	CameraSpringArm->SetupAttachment(this);

	// Camera Spring Arm Configure
	// Camera lag enables smooth panning
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 10.0;

	CameraSpringArm->TargetArmLength = TargetCameraZoomDistance;

	// Don't use pawn movement to move the camera, we are overriding all movement on the pawn (pawn will not move on its own)
	CameraSpringArm->bInheritPitch = false;
	CameraSpringArm->bInheritRoll = false;
	CameraSpringArm->bInheritYaw = false;

	// Disable any collision
	CameraSpringArm->bDoCollisionTest = false;

	CameraSpringArm->SetRelativeRotation(FRotator(295, 0, 0));
}

void URTS_SmoothCameraComponent::SetupCamera()
{
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	// Overrides motion blur for crisp movement
	Camera->PostProcessSettings.bOverride_MotionBlurAmount = true;
	Camera->PostProcessSettings.MotionBlurAmount = 0;
	Camera->PostProcessSettings.MotionBlurMax = 0;
}


// Called when the game starts
void URTS_SmoothCameraComponent::BeginPlay()
{
	Super::BeginPlay();
}

/** Sets the axis based on the configured input */
void URTS_SmoothCameraComponent::MoveCameraLeftRight(const float Value)
{
	MoveCamera(Value, 0, 1);
}

/** Sets the axis based on the configured input */
void URTS_SmoothCameraComponent::MoveCameraUpDown(const float Value)
{
	MoveCamera(0, Value, 1);
}

void URTS_SmoothCameraComponent::MoveCameraUpDownPerUnit(const float Value)
{	
	MoveCamera(0, (20 * Value) / CameraSpeed, 1);
}

void URTS_SmoothCameraComponent::MoveCameraLeftRightPerUnit(const float Value)
{
	MoveCamera((20 * Value) / CameraSpeed, 0, 1);
}

/** Sets the axis based on the configured input */
void URTS_SmoothCameraComponent::ZoomCamera(const float Value)
{
	// Axis will be zero when there is no active zoom direction
	if (FMath::IsNearlyZero(Value))
	{
		return;
	}

	float ZoomAmount;

	// Positive value means we are zooming out, while negative value means we are zooming in
	if (Value > 0) {
		ZoomAmount = CameraZoomPerUnit;
	}
	else {
		ZoomAmount = -CameraZoomPerUnit;
	}

	// Update the target distance within our bounds
	TargetCameraZoomDistance = FMath::Clamp(CameraSpringArm->TargetArmLength + ZoomAmount, MinCameraDistance, MaxCameraDistance);

}

/** Deactivates rotation mode */
void URTS_SmoothCameraComponent::RotateCameraReleased()
{
	bShouldRotateCamera = false;
}

/** Activates rotation mode and begins tracking mouse position */
void URTS_SmoothCameraComponent::RotateCameraPressed()
{
	bShouldRotateCamera = true;

	APlayerController* PlayerController = GetPlayerControllerForOwningPawn();

	if (!ensure(PlayerController != nullptr))
	{
		return;
	}

	PlayerController->GetMousePosition(RotateCameraMouseStart.X, RotateCameraMouseStart.Y);
}

APlayerController* URTS_SmoothCameraComponent::GetPlayerControllerForOwningPawn() const
{
	APawn* Pawn = GetOwningPawn();

	if (!ensure(Pawn != nullptr))
	{
		return nullptr;
	}

	return Pawn->GetController<APlayerController>();
}

APawn* URTS_SmoothCameraComponent::GetOwningPawn() const
{
	APawn* Pawn = GetOwner<APawn>();

	if (!ensure(Pawn != nullptr))
	{
		return nullptr;
	}

	return Pawn;
}




// Called every frame
void URTS_SmoothCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/** Horizontal axis input */
	float CameraLeftRightAxisValue;

	/** Vertical axis input */
	float CameraUpDownAxisValue;

	APlayerController* PlayerController = GetPlayerControllerForOwningPawn();
	if (!ensure(PlayerController != nullptr)) return;
	
	int ViewportSizeX, ViewportSizeY;
	// Get the current size of the viewport (depending on the game settings, the player might be able to resize the game window while playing)
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);

	float MouseX, MouseY;
	// Only respond to viewport edge scrolling if we are not currently rotating the camera
	// Value closer to -1.0 or 1.0 means full scroll speed, in between means a slower scroll speed (we start scrolling slowly and then speed up the closer your mouse gets to the edge
	if (PlayerController->GetMousePosition(MouseX, MouseY) && !bShouldRotateCamera)
	{

		// Recalculate our right and top borders
		const float ScrollBorderRight = MouseX / ViewportSizeX;
		const float ScrollBorderTop = MouseY / ViewportSizeY;

		// If we are scrolling from left edge
		if (ScrollBorderRight >= 0.75)
		{
			CameraLeftRightAxisValue = -1 * GetMaxAlpha(ScrollBorderRight);
		}
		else if (ScrollBorderRight <= 0.25) {
			CameraLeftRightAxisValue = GetMinAlpha(ScrollBorderRight);
		}
		else {
			CameraLeftRightAxisValue = 0;
		}

		if (ScrollBorderTop >= 0.75)
		{
			CameraUpDownAxisValue = -1 * GetMaxAlpha(ScrollBorderTop);
		} 
		else if (ScrollBorderTop <= 0.25) {
			CameraUpDownAxisValue = GetMinAlpha(ScrollBorderTop);
		}
		else {
			CameraUpDownAxisValue = 0;
		}
		
	}

	// Keep our values within our axis bounds
	CameraLeftRightAxisValue = FMath::Clamp(CameraLeftRightAxisValue, -1.0f, +1.0f);
	CameraUpDownAxisValue = FMath::Clamp(CameraUpDownAxisValue, -1.0f, +1.0f);

	if (!bShouldRotateCamera) {
		if (CameraLeftRightAxisValue != 0 || CameraUpDownAxisValue != 0) {
			MoveCamera(CameraLeftRightAxisValue, CameraUpDownAxisValue, DeltaTime);
		}

		// Zoom in or out as necessary
		if (!FMath::IsNearlyEqual(CameraSpringArm->TargetArmLength, TargetCameraZoomDistance, 0.5f))
		{
			// This allows us to smoothly zoom to our desired target arm length over time
			CameraSpringArm->TargetArmLength = FMath::FInterpTo(CameraSpringArm->TargetArmLength, TargetCameraZoomDistance,
				DeltaTime, CameraZoomSpeed);
		}
	}
	
	if (bShouldRotateCamera)
	{
		FVector2D MouseLocation;
		PlayerController->GetMousePosition(MouseLocation.X, MouseLocation.Y);

		// Get how much we have moved since the last frame/rotate start
		const float XPercent = (MouseLocation.X - RotateCameraMouseStart.X) / ViewportSizeX;
		const float YPercent = (RotateCameraMouseStart.Y - MouseLocation.Y) / ViewportSizeY;

		RotateCamera(XPercent, YPercent);

		// Update the "last frame" mouse location
		RotateCameraMouseStart = MouseLocation;
	}

}

void URTS_SmoothCameraComponent::MoveCamera(const float CameraLeftRightAxisValue, const float CameraUpDownAxisValue, const float DeltaTime) {
	
	APawn* Pawn = GetOwningPawn();
	if (!ensure(Pawn != nullptr)) return;

	FVector Location = Pawn->GetActorLocation();

	// Update the left/right movement based on the direction to the right of where we are facing
	Location += CameraSpringArm->GetRightVector() * CameraSpeed * CameraLeftRightAxisValue * DeltaTime;

	// Update the forward/backwards movement based on the yaw rotation, **ignoring pitch** so the camera remains level as it moves (looking down would otherwise pan the camera forward and down)
	Location += FRotationMatrix(FRotator(0, CameraSpringArm->GetRelativeRotation().Yaw, 0)).GetScaledAxis(EAxis::X) * CameraSpeed * CameraUpDownAxisValue * DeltaTime;

	// TODO add camera bounds to level
	//if (!CameraBoundsVolume || CameraBoundsVolume->EncompassesPoint(Location))
	//{
	// Update the pawn's location and the camera will follow
	Pawn->SetActorLocation(Location);
	//}	
}

float URTS_SmoothCameraComponent::GetMaxAlpha(float difference) const {
	return (difference - 0.75) * 4;
}
float inline URTS_SmoothCameraComponent::GetMinAlpha(float difference) const {
	return 1 - (difference * 4);
}

void URTS_SmoothCameraComponent::PanCamera(const float Value) {
	float XPercent = CameraPanPerUnit / 180 * Value;
	RotateCamera(XPercent, 0);
}

void URTS_SmoothCameraComponent::PitchCamera(const float Value) {
	float YPercent = CameraPitchPerUnit / 180 * Value;
	RotateCamera(0, YPercent);
}

void URTS_SmoothCameraComponent::RotateCamera(const float XPercent, const float YPercent) {
	// Get the current rotation within -180 to 180 degrees, instead of 0-360
	FRotator CurrentRot = CameraSpringArm->GetRelativeRotation().GetNormalized();

	// Update our rotation based on 100% movement equals 180 degrees rotation, limiting pitch to near vertical to limit issues at -90 and 90 degrees
	CurrentRot = FRotator(FMath::Clamp<float>(CurrentRot.Pitch + (YPercent * 180), CameraMaximumPitch, CameraMinimumPitch),
		CurrentRot.Yaw + (XPercent * 180), 0);
	
	CameraSpringArm->SetRelativeRotation(CurrentRot);
}

