// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskNode/BTTask_QuestAccessibility.h"
#include "Character/BaseNPC.h"
#include "Subsystem/QuestEngineSubsystem.h"

UBTTask_QuestAccessibility::UBTTask_QuestAccessibility()
{
	NodeName = TEXT("Check Quest Accessibility");
}

EBTNodeResult::Type UBTTask_QuestAccessibility::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	bNotifyTick = true;

	if (OwnerComp.GetOwner() == nullptr) return EBTNodeResult::Failed;

	const auto OwnerActorController = Cast<AController>(OwnerComp.GetOwner());
	const auto OwnerActorControllerCharacter = Cast<ABaseNPC>(OwnerActorController->GetCharacter());
	GetQuestSpeakerComponent = OwnerActorControllerCharacter->GetSpeakerQuestComponent();

	const auto QuestSubsystem = GEngine->GetEngineSubsystem<UQuestEngineSubsystem>();
	QuestManager = QuestSubsystem->GetQuestManager();
	return EBTNodeResult::InProgress;
}

void UBTTask_QuestAccessibility::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!OwnerComp.GetOwner()) return;

	if (ThisQuestID == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("This NPC ID defaults is 0, please set according to the current NPC ID!"));
		return;
	}
	
	if (QuestManager->GetIndexQuestCompleted().Contains(ThisQuestID))
	{
		QuestState = EQuestState::EQS_Completed;
	}
	else
	{
		if (ThisQuestID == QuestManager->GetIndexQuest())
		{
			QuestState = EQuestState::EQS_InProgress;
		}
		else
		{
			QuestState = EQuestState::EQS_Unavailable;
		}
	}

	QuestManager->SetQuestState(QuestState, ThisQuestID);
	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}
