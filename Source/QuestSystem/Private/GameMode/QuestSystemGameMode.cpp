// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameMode/QuestSystemGameMode.h"
#include "UObject/ConstructorHelpers.h"

AQuestSystemGameMode::AQuestSystemGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
