// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Structure/QuestStructure.h"
#include "QuestManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestState, EQuestState, State, int32, ID);

UCLASS()
class QUESTSYSTEM_API UQuestManager : public UObject
{
	GENERATED_BODY()

public:
	void SetQuestManager();
	void SetQuestState(EQuestState State, int32 ID);
	
	UFUNCTION()
	void GetCurrentQuest(int32 QuestID);

	UPROPERTY(BlueprintAssignable)
	FOnQuestState OnQuestState;

	TArray<int32> IndexQuestCompleted;
	
private:
	int32 IndexQuest = 1;
	EQuestState QuestState;

public:
	FORCEINLINE int32 GetIndexQuest() const {return IndexQuest;}
	FORCEINLINE EQuestState GetQuestState() const {return QuestState;}
	FORCEINLINE EQuestState SetQuestAvailable(EQuestState State) {return QuestState = State;}
	FORCEINLINE TArray<int32> GetIndexQuestCompleted() {return IndexQuestCompleted;}
};
