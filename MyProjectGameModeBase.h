// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "UserProfile.h"
#include "RTSCameraPawn.h"

#include "MyProjectGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMyProjectGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	AMyProjectGameModeBase();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UClassNames")
	TSubclassOf<UUserProfile> UPBlueprintClassName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameDesign")
	UUserProfile* userProfile;

	void BeginPlay();
};
