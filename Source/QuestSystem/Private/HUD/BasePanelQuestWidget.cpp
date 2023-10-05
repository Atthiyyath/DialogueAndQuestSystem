// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/BasePanelQuestWidget.h"
#include "Components/ScrollBox.h"
#include "HUD/ListQuestWidget.h"

void UBasePanelQuestWidget::SetupQuestTitle(FString QuestText)
{
	// override function!
	if (!ListQuestWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please insert the WBP_ListQuest first!"))
		return;
	}
	
	QuestWidget = CreateWidget<UListQuestWidget>(this, ListQuestWidgetClass);
	ScrollQuest->AddChild(QuestWidget);
	QuestWidget->SetupQuestTitle(QuestText);
}

void UBasePanelQuestWidget::SetupQuestDesc(FString QuestText)
{
	// override function!
	QuestWidget->SetupQuestDesc(QuestText);
}

void UBasePanelQuestWidget::ClearQuest()
{
	// override function!
	ScrollQuest->ClearChildren();
}
