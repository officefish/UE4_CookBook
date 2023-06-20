// Copyright Epic Games, Inc. All Rights Reserved.


#include "MyProjectGameModeBase.h"

AMyProjectGameModeBase::AMyProjectGameModeBase() 
	:
	AGameModeBase()
{
	DefaultPawnClass = ARTSCameraPawn::StaticClass();
}

void AMyProjectGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	AMyProjectGameModeBase* gm = Cast<AMyProjectGameModeBase>(GetWorld()->GetAuthGameMode());

	if (gm)
	{
		//UUserProfile* userProfileWithConstruct = ConstructObject<UUserProfile>(gm->UPBlueprintClassName);

		// Create object with NewObject Constructor
		this->userProfile = NewObject<UUserProfile>((UObject*)GetTransientPackage(),
		UUserProfile::StaticClass());

		//UUserProfile* userProfile2 = NewObject<UUserProfile>(this, UUserProfile::StaticClass());
		
		// Destroy object
		if (userProfile)
		{
			UE_LOG(LogTemp, Warning, TEXT("New Instance of UserProfile created"));
			
			//userProfile->ConditionalBeginDestroy();
			//userProfile = nullptr;

			//UE_LOG(LogTemp, Warning, TEXT("New Instance of UserProfile destroyed"));
		}


	}

	// Basic UE_LOG message
	//UE_LOG(LogTemp, Warning, TEXT("Some warning message"));

	// UE_LOG message with arguments
	//int intVar = 5;
	//float floatVar = 3.7f;
	//FString fstringVar = "an fstring variable";
	//UE_LOG(LogTemp, Warning, TEXT("Text, %d %f %s"), intVar, floatVar, *fstringVar);

	// FString::Printf() method
	//FString name = "Tim";
	//int32 mana = 450;
	//FString string = FString::Printf(TEXT("Printf() - Name = %s Mana = %d"), *name, mana);

	// FString::Format() method
	//TArray< FStringFormatArg > args;
	//args.Add(FStringFormatArg(name));
	//args.Add(FStringFormatArg(mana));
	//string = FString::Format(TEXT("Format() - Name = {0} Mana = {1}"), args);
	//UE_LOG(LogTemp, Warning, TEXT("Your string: %s"), *string);
}