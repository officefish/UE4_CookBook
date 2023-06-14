// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include <string>
#include "ColoredTexture.h"
#include "UserProfile.generated.h"

UENUM()
enum Status
{
	Stopped     UMETA(DisplayName = "Stopped"),
	Moving      UMETA(DisplayName = "Moving"),
	Attacking   UMETA(DisplayName = "Attacking"),
};

// UCLASS macro options sets this C++ class to be
// Blueprintable within the UE4 Editor
UCLASS(Blueprintable)
class MYPROJECT_API UUserProfile : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
	float Energy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserProfile")
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UserProfile")
	FString Email;

	// Displays any UClasses deriving from UObject in a dropdown 
	// menu in Blueprints
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Unit")
	TSubclassOf<UObject> UClassOfPlayer;

	// Displays string names of UCLASSes that derive from
	// the GameMode C++ base class
	UPROPERTY(EditAnywhere, meta = (MetaClass = "GameMode"), Category = "Unit")
	FStringClassReference UClassGameMode;

	// Custom struct example
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	FColoredTexture Texture;

	// Enum example
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GamePlay")
	TEnumAsByte<Status> status;

	UFUNCTION(BlueprintCallable, Category = Properties)
	FString ToString();


};
