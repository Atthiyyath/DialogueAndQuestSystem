// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ListQuestWidget.h"
#include "Components/TextBlock.h"

void UListQuestWidget::SetupQuestTitle(FString QuestText)
{
	QuestTitle->SetText(FText::FromString(QuestText));
}

void UListQuestWidget::SetupQuestDesc(FString QuestText)
{
	QuestDesc->SetText(FText::FromString(QuestText));
}
