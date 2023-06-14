// Fill out your copyright notice in the Description page of Project Settings.


#include "UserProfile.h"

FString UUserProfile::ToString() {
	return FString::Printf(TEXT("An instance of UProfile: %s, %s"),
		*Username, *Email);

}

