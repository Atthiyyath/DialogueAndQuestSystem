// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskNode/BTTask_StopDialogue.h"
#include "Character/BaseNPC.h"
#include "Component/PlayerHUDComponent.h"
#include "Component/SpeakerDialogueComponent.h"
#include "Component/SpeakerQuestComponent.h"
#include "DataTable/QuestDataTable.h"
#include "HUD/PlayerHUD.h"
#include "HUD/GameMainWidget.h"
#include "Kismet/GameplayStatics.h"

UBTTask_StopDialogue::UBTTask_StopDialogue()
{
	NodeName = TEXT("Stop Dialogue");
}

EBTNodeResult::Type UBTTask_StopDialogue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	bNotifyTick = true;

	if (OwnerComp.GetOwner() == nullptr) return EBTNodeResult::Failed;

	const auto OwnerActorController = Cast<AController>(OwnerComp.GetOwner());
	const auto OwnerActorControllerCharacter = Cast<ABaseNPC>(OwnerActorController->GetCharacter());
	const auto GetDialogueSpeakerComponent = OwnerActorControllerCharacter->GetSpeakerDialogueComponent();
	GetQuestSpeakerComponent = OwnerActorControllerCharacter->GetSpeakerQuestComponent();

	const auto QuestSubsystem = GEngine->GetEngineSubsystem<UQuestEngineSubsystem>();
	QuestManager = QuestSubsystem->GetQuestManager();
	if (!QuestManager) return EBTNodeResult::Failed;
	
	OnNextDialogue.AddDynamic(GetDialogueSpeakerComponent, &USpeakerDialogueComponent::OnNextDialogue);
	OnQuestIndex.AddDynamic(QuestManager, &UQuestManager::GetCurrentQuest);

	const AHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD();
	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("AHUD is null"));
		return EBTNodeResult::Failed;
	}
	PlayerHUDComponent = Cast<UPlayerHUDComponent>(HUD->GetComponentByClass(UPlayerHUDComponent::StaticClass()));
	if (!PlayerHUDComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please assign the PlayerHUDComponent ActorComponent to your AHUD!"));
		return EBTNodeResult::Failed;
	}

	GameMainWidget = PlayerHUDComponent->GetMainDisplay();
	if (!GameMainWidget) return EBTNodeResult::Failed;

	return EBTNodeResult::InProgress;
}

void UBTTask_StopDialogue::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!OwnerComp.GetOwner()) return;

	if (GameMainWidget->GetDialogueFinish(true))
	{
		GameMainWidget->ContinueDialogue();
		GameMainWidget->EndDialogue();
		PlayerHUDComponent->ActivateDialogue(false);
		
		if (NewKey == 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("Set NewKey Dialogue is null!"));
			return;
		}

		if (!OnNextDialogue.IsBound()) return;
		OnNextDialogue.Broadcast(NewKey);

		if (DialogueType == EDialogueType::EDT_Quest)
		{
			if (!QuestDataTable)
			{
				UE_LOG(LogTemp, Warning, TEXT("Quest Data Table is null!"));
				return;
			}
			
			const auto QuestRowActive = FString::FromInt(QuestManager->GetIndexQuest());
			const FQuestDataTable* DT = QuestDataTable->FindRow<FQuestDataTable>(FName(*QuestRowActive), "");
			if (!DT) return;

			if (DT->NextQuestIndex == 0)
			{
				UE_LOG(LogTemp, Warning, TEXT("Set NextQuestIndex Quest is null!"));
				return;
			}

			if (!OnQuestIndex.IsBound()) return;
			if (QuestType == EQuestType::EQT_SetAvailable)
			{
				OnQuestIndex.Broadcast(DT->QuestIndex);
			}
			else
			{
				OnQuestIndex.Broadcast(DT->NextQuestIndex);
			}

			if (!GetQuestSpeakerComponent) return;
			GetQuestSpeakerComponent->QuestAvailability();
		}

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
