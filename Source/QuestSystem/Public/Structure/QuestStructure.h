#pragma once

#include "Engine/DataTable.h"
#include "QuestStructure.generated.h"

UENUM(BlueprintType)
enum class EQuestState : uint8
{
	EQS_Unavailable		UMETA(Display = "Quest Unavailable"),
	EQS_Available		UMETA(Display = "Quest Available"),
	EQS_InProgress		UMETA(Display = "Quest In Progress"),
	EQS_Completed		UMETA(Display = "Quest Completed"),
	EQS_Failed			UMETA(Display = "Quest Failed")
};


USTRUCT()
struct FQuestStructure
{
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly, Category = Quest)
	UDataTable* QuestDataTable;

	UPROPERTY(EditInstanceOnly, Category = Quest)
	int32 ActorID = 0;
};