// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/SpeakerQuestComponent.h"
#include "Character/QuestSystemCharacter.h"
#include "Component/PlayerQuestComponent.h"
#include "DataTable/QuestDataTable.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/QuestManager.h"
#include "HUD/GameMainWidget.h"

USpeakerQuestComponent::USpeakerQuestComponent()
{
	
}

void USpeakerQuestComponent::BeginPlay()
{
	Super::BeginPlay();
		
	if (QuestStructure.ActorID == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Fill up the ActorID (SpeakerQuestComponent->ActorID) to ensure which QuestID will taken according to QuestDataTable"));
		return;
	}
	
	if (QuestStructure.ActorID == 1) QuestState = EQuestState::EQS_Available;
	if (!QuestManager) return;
	QuestManager->SetQuestState(QuestState, QuestStructure.ActorID);
	
	QuestManager->OnQuestState.AddDynamic(this, &USpeakerQuestComponent::UpdateQuestState);
}

void USpeakerQuestComponent::QuestAvailability()
{
	Super::QuestAvailability();

	const auto RowAsInt = QuestManager->GetIndexQuest();
	const auto QuestRowActive = FString::FromInt(RowAsInt);
	const FQuestDataTable* DT = QuestStructure.QuestDataTable->FindRow<FQuestDataTable>(FName(*QuestRowActive), "");
	if (!DT) return;
	
	if (QuestStructure.ActorID == RowAsInt)
	{
		if(!OnQuestCompleted.IsAlreadyBound(MainWidget, &UGameMainWidget::QuestCompleted))
			OnQuestCompleted.AddDynamic(MainWidget, &UGameMainWidget::QuestCompleted);
		
		QuestState = EQuestState::EQS_InProgress;
		if (!QuestManager) return;
		QuestManager->SetQuestState(QuestState, QuestStructure.ActorID);
		
		if (!MainWidget->OnQuestActive.IsBound()) return;
		MainWidget->OnQuestActive.Broadcast(DT->QuestIndex);
	}
}

void USpeakerQuestComponent::CheckProgress(const TArray<int32>& ItemCollected)
{
	Super::CheckProgress(ItemCollected);

	const auto RowAsInt = QuestManager->GetIndexQuest();
	const auto QuestRowActive = FString::FromInt(RowAsInt);
	const FQuestDataTable* DT = QuestStructure.QuestDataTable->FindRow<FQuestDataTable>(FName(*QuestRowActive), "");
	if (!DT) return;

	if (QuestState != EQuestState::EQS_InProgress) return;
	if (QuestStructure.ActorID == RowAsInt)
	{
		UE_LOG(LogTemp, Warning, TEXT("Collect %d items from %d ItemCollected"), ItemCollected.Num(), DT->Objectives.Num());;

		if (ItemCollected.Num() != DT->Objectives.Num()) return;
		QuestCompleted();
	}
}

void USpeakerQuestComponent::QuestCompleted()
{
	Super::QuestCompleted();

	QuestState = EQuestState::EQS_Completed;
	
	if (!QuestManager) return;	
	QuestManager->IndexQuestCompleted.Add(QuestStructure.ActorID);
	QuestManager->SetQuestState(QuestState, QuestStructure.ActorID);
 
	if (!OnQuestCompleted.IsBound()) return;
	OnQuestCompleted.Broadcast();
	
	const ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	const auto PlayerQuestComponent = Cast<UPlayerQuestComponent>(Character->GetComponentByClass(UPlayerQuestComponent::StaticClass()));
	if (!PlayerQuestComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please add the PlayerQuestComponent on PlayerCharacter first!"));
		return;
	}
	PlayerQuestComponent->CollectibleItem.Empty();
	
	UE_LOG(LogTemp, Warning, TEXT("Quest Completed"));
}

void USpeakerQuestComponent::UpdateQuestState(EQuestState InQuestState, int32 ID)
{	
	if (QuestStructure.ActorID == ID)
	{
		QuestState = InQuestState;
	}	
}
