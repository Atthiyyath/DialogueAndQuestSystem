// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePanelQuestWidget.h"
#include "PanelQuestWidget.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UPanelQuestWidget : public UBasePanelQuestWidget
{
	GENERATED_BODY()

public:
	virtual void SetupQuestTitle(FString QuestText) override;
	virtual void SetupQuestDesc(FString QuestText) override;
};
