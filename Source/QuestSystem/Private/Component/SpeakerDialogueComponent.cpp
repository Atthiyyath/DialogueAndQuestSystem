// Fill out your copyright notice in the Description page of Project Settings.

#include "Component/SpeakerDialogueComponent.h"
#include "Component/PlayerDialogueComponent.h"
#include "LevelSequencePlayer.h"
#include <LevelSequence/Public/LevelSequenceActor.h>
#include "Component/PlayerHUDComponent.h"
#include "Controller/DialogueController.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/PlayerHUD.h"
#include "HUD/GameMainWidget.h"

USpeakerDialogueComponent::USpeakerDialogueComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void USpeakerDialogueComponent::BeginPlay()
{
	Super::BeginPlay();

	SequenceActor = Cast<ALevelSequenceActor>(UGameplayStatics::GetActorOfClass(this, ALevelSequenceActor::StaticClass()));
	DialogueController = Cast<ADialogueController>(GetOwner()->GetInstigatorController());
	
	const AHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD();
	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("AHUD is null"));
		return;
	}
	PlayerHUDComponent = Cast<UPlayerHUDComponent>(HUD->GetComponentByClass(UPlayerHUDComponent::StaticClass()));
	if (!PlayerHUDComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please assign the PlayerHUDComponent ActorComponent to your AHUD!"));
		return;
	}
}

void USpeakerDialogueComponent::SetupSequencer(UPlayerDialogueComponent* PlayerDialogueComponent)
{
	if (!PlayerDialogueComponent) return;
	
	for (const TPair<int32, FDialogueData> &Pair : DialogueData)
	{
		FDialogueData Value = Pair.Value;

		int32 ID = Pair.Key;
		if (ID == 0)
		{
			Value.IsActive = true;
		}
		
		if (Value.IsActive == true)
		{
			if (!SequenceActor)
			{
				SequenceActor = Cast<ALevelSequenceActor>(GetWorld()->SpawnActor<ALevelSequenceActor>());
			}

			ULevelSequence* CutsceneSequence = Value.Cutscene;
			if (SequenceActor)
			{
				SequenceActor->SetSequence(CutsceneSequence);
				SequenceActor->SequencePlayer->Play();
			}

			if (AActor* FindActorPosition = Value.ActorPosition)
			{
				PlayerDialogueComponent->GetOwner()->SetActorLocation(FindActorPosition->GetActorLocation());
				PlayerDialogueComponent->GetOwner()->SetActorRotation(FindActorPosition->GetActorRotation());
			}
		}
	}
}

void USpeakerDialogueComponent::SetupDialogueTree()
{
	if (DialogueData.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Dialogue Data Null"));
		return;
	}

	const FDialogueData Data = DialogueData[NextIndex];
	if (!Data.StaticStruct()) return;

	UBehaviorTree* BT = Data.DialogueTree;
	if (!BT) return;
	
	if (!DialogueController) return;
	DialogueController->RunBehaviorTree(BT);
}

void USpeakerDialogueComponent::StopDialogueTree()
{
	DialogueController->StopBehaviourTree();
}

void USpeakerDialogueComponent::PlayCutscene() const
{
	if (!SequenceActor) return;	
	SequenceActor->SequencePlayer->Play();
}

void USpeakerDialogueComponent::UpdateDialogue()
{
	if (!SequenceActor) return;	
	SequenceActor->SequencePlayer->Pause();

	PlayerHUDComponent->GetMainDisplay()->SetDialogueFinish(true);
}

void USpeakerDialogueComponent::StopCutscene()
{
	if (!SequenceActor) return;
	SequenceActor->SequencePlayer->Stop();
}

void USpeakerDialogueComponent::OnNextDialogue(int32 InNextIndex)
{
	NextIndex = InNextIndex;
}

