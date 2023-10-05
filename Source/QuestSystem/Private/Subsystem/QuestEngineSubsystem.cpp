// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/QuestEngineSubsystem.h"

UQuestEngineSubsystem::UQuestEngineSubsystem()
{
	
}

void UQuestEngineSubsystem::SetQuestManager(UQuestManager* InQuestManager)
{
	QuestManager = InQuestManager;
}

void UQuestEngineSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UQuestEngineSubsystem::Deinitialize()
{
	Super::Deinitialize();

	QuestManager = nullptr;
}

void UQuestEngineSubsystem::QuestData()
{
	IndexQuest = QuestManager->GetIndexQuest();
}

UQuestManager* UQuestEngineSubsystem::GetQuestManager()
{
	if (!QuestManager)
	{
		QuestManager = NewObject<UQuestManager>();
		QuestManager->SetQuestManager();
	}

	return QuestManager;
}
