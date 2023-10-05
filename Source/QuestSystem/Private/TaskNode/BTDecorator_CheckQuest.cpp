// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskNode/BTDecorator_CheckQuest.h"
#include "Component/SpeakerQuestComponent.h"
#include "Manager/QuestManager.h"

void UBTDecorator_CheckQuest::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);
}

bool UBTDecorator_CheckQuest::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	
	const auto QuestSubsystem = GEngine->GetEngineSubsystem<UQuestEngineSubsystem>();
	const auto QuestManager = QuestSubsystem->GetQuestManager();
	
	if (QuestState == QuestManager->GetQuestState())
	{
		return true;
	}
	return false;
}
