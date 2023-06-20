// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "RTS_SmoothCameraComponent.h"

#include "PC_WithRTSCamera.generated.h"

class APawn;

/**
 * 
 */
UCLASS()
class MYPROJECT_API APC_WithRTSCamera : public APlayerController
{
	GENERATED_BODY()

public:
	//APC_WithRTSCamera();

	virtual void SetupInputComponent() override;
	//virtual void BeginPlay() override;

private:
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();

};
