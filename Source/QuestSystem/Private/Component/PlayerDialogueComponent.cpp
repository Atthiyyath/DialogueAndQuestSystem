// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PlayerDialogueComponent.h"
#include "Interface/InteractableInterface.h"
#include "Character/QuestNPC.h"
#include "Component/SpeakerDialogueComponent.h"

class IInteractableInterface;

UPlayerDialogueComponent::UPlayerDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UPlayerDialogueComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerDialogueComponent::OnEnterActor(AActor* OnInteractiveActor)
{
	if (!OnInteractiveActor) return;
	CurrentInteractiveActor = OnInteractiveActor;
}

void UPlayerDialogueComponent::OnLeaveActor()
{
	CurrentInteractiveActor = nullptr;
}

void UPlayerDialogueComponent::StartDialogue() const
{
	IInteractableInterface* Interface = Cast<IInteractableInterface>(CurrentInteractiveActor);
	if (!Interface) return;

	Interface->OnInteract();
}

void UPlayerDialogueComponent::PlayCutsene()
{
	NPC = Cast<AQuestNPC>(CurrentInteractiveActor);
	if (!NPC) return;
	NPC->GetSpeakerDialogueComponent()->PlayCutscene();
}

void UPlayerDialogueComponent::StopCutscene()
{
	NPC = Cast<AQuestNPC>(CurrentInteractiveActor);
	if (!NPC) return;
	NPC->GetSpeakerDialogueComponent()->StopCutscene();
	NPC->GetSpeakerDialogueComponent()->StopDialogueTree();
}

