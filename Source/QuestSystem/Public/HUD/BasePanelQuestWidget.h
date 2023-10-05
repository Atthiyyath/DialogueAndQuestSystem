// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BasePanelQuestWidget.generated.h"

class UTextBlock;

UCLASS()
class QUESTSYSTEM_API UBasePanelQuestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetupQuestTitle(FString QuestText);
	virtual void SetupQuestDesc(FString QuestText);
	virtual void ClearQuest();
	
private:
	class UListQuestWidget* QuestWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Quest, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UListQuestWidget> ListQuestWidgetClass;

	// Bind Widgets
	UPROPERTY(BlueprintReadOnly, Category = Quest, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	class UScrollBox* ScrollQuest;
};
