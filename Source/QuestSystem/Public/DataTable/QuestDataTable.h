// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Actor/CollectibleItem.h"
#include "QuestDataTable.generated.h"

UENUM(BlueprintType)
enum class EPlayMode : uint8
{
	EPM_CasualPlay			UMETA(Display = "Casual Play"),
	EPM_CompetitivePlay		UMETA(Display = "Competitive Play")
};

USTRUCT(BlueprintType)
struct FObjectives
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	TSubclassOf<ACollectibleItem> Item;

	UPROPERTY(EditInstanceOnly, Category = Quest)
	FString Description;
};

USTRUCT(BlueprintType)
struct QUESTSYSTEM_API FQuestDataTable : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	int32 QuestIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FString QuestTitle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	FString QuestDesc;

	UPROPERTY(EditInstanceOnly, Category = Quest)
	TMap<int32, FObjectives> Objectives;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Quest)
	int32 NextQuestIndex = 0;
};
