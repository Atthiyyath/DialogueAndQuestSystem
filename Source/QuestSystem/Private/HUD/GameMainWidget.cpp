// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameMainWidget.h"
#include "HUD/PanelDialogue.h"
#include "HUD/PanelQuestWidget.h"
#include "HUD/PanelObjectivesQuestWidget.h"
#include "Component/PlayerDialogueComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DataTable/QuestDataTable.h"
#include "GameFramework/Character.h"

void UGameMainWidget::InitWidget()
{
	Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	
	PanelDialogue->SetVisibility(ESlateVisibility::Hidden);
	PlayerQuestWidget->SetVisibility(ESlateVisibility::Hidden);
	PanelObjectivesQuestWidget->SetVisibility(ESlateVisibility::Hidden);

	if (!OnQuestActive.IsAlreadyBound(this, &UGameMainWidget::SetupQuestActive))
		OnQuestActive.AddDynamic(this, &UGameMainWidget::SetupQuestActive);

	PlayerDialogueComponent = Cast<UPlayerDialogueComponent>(Player->GetComponentByClass(UPlayerDialogueComponent::StaticClass()));
	if (!PlayerDialogueComponent) return;
}

void UGameMainWidget::SetupDialogueActive(bool IsActive)
{
	const ESlateVisibility RenderValue = IsActive ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	PanelDialogue->SetVisibility(RenderValue);

	if (IsActive)
	{
		PanelObjectiveQuestVisibility(IsActive);
		LockCharacter(IsActive);
		IsDialogueActive = IsActive;
	}
	else
	{
		PanelObjectiveQuestVisibility(IsActive);
		LockCharacter(IsActive);
		IsDialogueActive = IsActive;
	}
}

void UGameMainWidget::SetupDialogueText(FString Dialogue)
{
	if (!PanelDialogue) return;
	PanelDialogue->SetDialogueActive(true);

	if (!IsDialogueFinished) return;
	PanelDialogue->SetupDialogue(Dialogue);
}

void UGameMainWidget::PlayCutscene() const
{
	if (!Player) return;
	PlayerDialogueComponent->PlayCutsene();
}

void UGameMainWidget::ContinueDialogue()
{
	IsDialogueFinished = false;
}

void UGameMainWidget::EndDialogue()
{
	if (!Player) return;
	PlayerDialogueComponent->StopCutscene();
	IsDialogueActive = false;
	SetupDialogueActive(false);
}

void UGameMainWidget::StartOption(TArray<FString> Options)
{
	PanelDialogue->SetupOption(Options);
	GameMode(false);
}

void UGameMainWidget::ShowOption()
{
	if (IsOptionSelected)
	{
		PanelDialogue->SetOptionActive(false);
	}
	PanelDialogue->SetOptionActive(true);
}

void UGameMainWidget::CloseOption()
{
	IsOptionSelected = false;
	GameMode(true);
	PanelDialogue->CloseOption();
}

void UGameMainWidget::ChooseOption(FString Option)
{
	OptionSelected = Option;
	IsOptionSelected = true;
}

void UGameMainWidget::LockCharacter(bool IsOccupied)
{
	IsOccupied ? Player->DisableInput(PlayerController) : Player->EnableInput(PlayerController);
}

void UGameMainWidget::GameMode(bool IsPlaying) const
{
	if (IsPlaying)
	{
		const FInputModeGameOnly GameOnly;		 
		PlayerController->SetShowMouseCursor(false);
		PlayerController->SetInputMode(GameOnly);
	}
	else
	{
		const FInputModeGameAndUI UIOnly;
		PlayerController->SetShowMouseCursor(true);
		PlayerController->SetInputMode(UIOnly);
	 }
}

void UGameMainWidget::PanelQuestVisibility(bool IsVisible) const
{
	const ESlateVisibility RenderValue = IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	PlayerQuestWidget->SetVisibility(RenderValue);
	PanelObjectiveQuestVisibility(IsVisible);
}

void UGameMainWidget::PanelObjectiveQuestVisibility(bool IsVisible) const
{
	const ESlateVisibility IsShowing = IsVisible ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
	PanelObjectivesQuestWidget->SetVisibility(IsShowing);
}

void UGameMainWidget::SetupQuestActive(int32 QuestIndex)
{
	if (!QuestDataTable)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please insert the Quest Data Table in WBP_GameMainWidget first!"));
		return;
	}
	
	const auto QuestID = FString::FromInt(QuestIndex);
	const FQuestDataTable* QuestStructure = QuestDataTable->FindRow<FQuestDataTable>(FName(*QuestID), "");
	if (!QuestStructure) return;
	
	PlayerQuestWidget->SetupQuestTitle(QuestStructure->QuestTitle);
	PlayerQuestWidget->SetupQuestDesc(QuestStructure->QuestDesc);
	PanelObjectivesQuestWidget->SetupQuestTitle(QuestStructure->QuestTitle);
	PanelObjectivesQuestWidget->SetupQuestDesc(QuestStructure->QuestDesc);
}

void UGameMainWidget::QuestCompleted()
{
	PlayerQuestWidget->ClearQuest();
	PanelObjectivesQuestWidget->ClearQuest();
}
