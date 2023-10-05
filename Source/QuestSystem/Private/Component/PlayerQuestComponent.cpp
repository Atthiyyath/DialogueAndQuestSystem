// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PlayerQuestComponent.h"
#include "Character/QuestNPC.h"
#include "Component/SpeakerQuestComponent.h"

UPlayerQuestComponent::UPlayerQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UPlayerQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UPlayerQuestComponent::OnEnterActor(AActor* OnInteractiveActor)
{
	if (!OnInteractiveActor) return;
	CurrentInteractiveActor = OnInteractiveActor;

	const auto NPC = Cast<AQuestNPC>(CurrentInteractiveActor);
	if (!NPC)
	{
		UE_LOG(LogTemp, Warning, TEXT("NPCs are null"));
		return;
	}
	
	const auto SpeakerQuestComp = NPC->GetSpeakerQuestComponent();
	if (!SpeakerQuestComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpeakerQuestComp is null"));
		return;
	}

	if(!OnAddCollectibleItems.IsAlreadyBound(SpeakerQuestComp, &USpeakerQuestComponent::CheckProgress))
		OnAddCollectibleItems.AddDynamic(SpeakerQuestComp, &USpeakerQuestComponent::CheckProgress);
}

void UPlayerQuestComponent::OnLeaveActor()
{
	CurrentInteractiveActor = nullptr;
}

void UPlayerQuestComponent::CheckIndex(int32 Index)
{
	ItemID = Index;
	if (QuestManager->GetIndexQuest() == ItemID)
	{
		CollectibleItem.Add(ItemID);
		if (!OnAddCollectibleItems.IsBound()) return;
		OnAddCollectibleItems.Broadcast(CollectibleItem);
	}
}

