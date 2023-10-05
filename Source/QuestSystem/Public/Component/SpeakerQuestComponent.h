// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Component/BaseQuestComponent.h"
#include "SpeakerQuestComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnQuestCompleted);

UCLASS()
class QUESTSYSTEM_API USpeakerQuestComponent : public UBaseQuestComponent
{
	GENERATED_BODY()

public:	
	USpeakerQuestComponent();
	
	virtual void QuestAvailability() override;
	virtual void CheckProgress(const TArray<int32>& ItemCollected) override;
	virtual void QuestCompleted() override;
	
	UFUNCTION()
	void UpdateQuestState(EQuestState InQuestState, int32 ID);
	
	UPROPERTY(BlueprintAssignable)
	FOnQuestCompleted OnQuestCompleted;
	
	UPROPERTY(EditInstanceOnly, Category = Quest)
	FQuestStructure QuestStructure;

	UPROPERTY(VisibleInstanceOnly, Category = Quest)
	EQuestState QuestState = EQuestState::EQS_Unavailable;
	
protected:
	virtual void BeginPlay() override;
};
