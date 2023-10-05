// Fill out your copyright notice in the Description page of Project Settings.


#include "Manager/QuestManager.h"
#include "Subsystem/QuestEngineSubsystem.h"

void UQuestManager::SetQuestManager()
{
	UQuestEngineSubsystem* QuestSubsystem = GEngine->GetEngineSubsystem<UQuestEngineSubsystem>();
	QuestSubsystem->SetQuestManager(this);
}

void UQuestManager::GetCurrentQuest(int32 QuestID)
{
	IndexQuest = QuestID;
}

void UQuestManager::SetQuestState(EQuestState State, int32 ID)
{
	QuestState = State;
	OnQuestState.Broadcast(QuestState, ID);
}
