// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_WithRTSCamera.h"
//

void APC_WithRTSCamera::SetupInputComponent()
{
	// Always call this.
	Super::SetupInputComponent();

	// This is initialized on startup, you can go straight to binding
	InputComponent->BindAction("MoveForward", IE_Pressed, this, &APC_WithRTSCamera::MoveForward);
	InputComponent->BindAction("MoveBackward", IE_Pressed, this, &APC_WithRTSCamera::MoveBackward);
	InputComponent->BindAction("MoveLeft", IE_Pressed, this, &APC_WithRTSCamera::MoveLeft);
	InputComponent->BindAction("MoveRight", IE_Pressed, this, &APC_WithRTSCamera::MoveRight);

	//InputComponent->BindAxis("MoveLeft", this, &APC_WithRTSCamera::MoveLeft);
}


void APC_WithRTSCamera::MoveForward()
{
	UE_LOG(LogTemp, Warning, TEXT("APC::NoveForward"));
}

void APC_WithRTSCamera::MoveBackward()
{
	UE_LOG(LogTemp, Warning, TEXT("APC::NoveBackward"));
}

void APC_WithRTSCamera::MoveLeft()
{
	UE_LOG(LogTemp, Warning, TEXT("APC::NoveLeft"));
}

void APC_WithRTSCamera::MoveRight()
{
	UE_LOG(LogTemp, Warning, TEXT("APC::NoveRight"));
}

