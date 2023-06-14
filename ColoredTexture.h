#pragma once 

#include "Engine/Texture.h"
#include "UObject/ObjectMacros.h"
#include "ColoredTexture.generated.h"

USTRUCT(Blueprintable)
struct MYPROJECT_API FColoredTexture
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	UTexture* Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HUD")
	FLinearColor Color;
};