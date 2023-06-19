// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

#include "RTS_SmoothCameraComponent.generated.h"

//class UCameraComponent;
//class USpringArmComponent;
//class APawn;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API URTS_SmoothCameraComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URTS_SmoothCameraComponent();

	/* Constructor service агтсешщты*/
	void SetupDefaults();
	void SetupSpringArm();
	void SetupCamera();

	UFUNCTION(BlueprintCallable, Category = "SmoothCamera")
	void MoveCameraLeftRight(float Value);

	UFUNCTION(BlueprintCallable, Category = "SmoothCamera")
	void MoveCameraUpDown(float Value);

	UFUNCTION(BlueprintCallable, Category = "SmoothCamera")
	void RotateCameraPressed();
	
	UFUNCTION(BlueprintCallable, Category = "SmoothCamera")
	void RotateCameraReleased();

	UFUNCTION(BlueprintCallable, Category = "SmoothCamera")
	void ZoomCamera(float Value);

	UFUNCTION(BlueprintCallable, Category = "SmoothCamera")
	void PanCamera(float Value);

	UFUNCTION(BlueprintCallable, Category = "SmoothCamera")
	void PitchCamera(float Value);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SmoothCamera")
	UCameraComponent* Camera;

	/** This is the "boom arm" that the camera is attached to */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SmoothCamera")
	USpringArmComponent* CameraSpringArm;

	/** Rate camera moves when moving */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SmoothCamera", meta = (ClampMin = 0))
	float CameraSpeed;

	/** Rate camera moves when panning */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SmoothCamera", meta = (ClampMin = 1, ClampMax = 30))
	float CameraPanPerUnit;

	/** Rate camera moves when pitching */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SmoothCamera", meta = (ClampMin = 1, ClampMax = 30))
	float CameraPitchPerUnit;

	/** Rate at which the camera zooms to a desired zoom distance */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SmoothCamera")
	float CameraZoomSpeed;

	/** Amount the desired camera distance should change per zoom action */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SmoothCamera")
	float CameraZoomPerUnit;

	/** Maximum angle rotation angle */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SmoothCamera", meta = (ClampMin = "-88", ClampMax = "88"))
	float CameraMaximumPitch;

	/** Maximum angle rotation angle */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SmoothCamera", meta = (ClampMin = "-88", ClampMax = "88"))
	float CameraMinimumPitch;

	/** Min zoom distance */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SmoothCamera", meta = (ClampMin = 0))
	float MinCameraDistance;

	/** Max zoom distance */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SmoothCamera", meta = (ClampMin = 0))
	float MaxCameraDistance;

	/** Distance from cursor to edge of screen to start scrolling */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SmoothCamera", meta = (ClampMin = 0))
	int32 CameraScrollThreshold;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	/** Zoom "axis" (direction) input */
	float CameraZoomAxisValue;

	/** Activates when middle mouse button is pressed */
	bool bShouldRotateCamera;

	/** Desired zoom distance set by zooming in a direction */
	float TargetCameraZoomDistance;

	/** Tracks the mouse position when rotation starts */
	FVector2D RotateCameraMouseStart;

	/** Gets the player controller from the owning actor (assumed to be a pawn) */
	APlayerController* GetPlayerControllerForOwningPawn() const;

	/** Gets the owning pawn on this component (assumed owner is a pawn) */
	APawn* GetOwningPawn() const;

private:
	float inline GetMaxAlpha(float difference) const;
	float inline GetMinAlpha(float difference) const;
	void MoveCamera(const float CameraLeftRightAxisValue, const float CameraUpDownAxisValue, const float DeltaTime);
	void RotateCamera(const float XPersent, const float YPersent);
};
