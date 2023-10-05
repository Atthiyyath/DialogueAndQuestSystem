// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ListQuestWidget.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UListQuestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void SetupQuestTitle(FString QuestText);
	virtual void SetupQuestDesc(FString QuestText);

private:
	UPROPERTY(BlueprintReadOnly, Category = Quest, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UTextBlock* QuestTitle;
	
	UPROPERTY(BlueprintReadOnly, Category = Quest, meta = (BindWidget), meta = (AllowPrivateAccess = "true"))
	UTextBlock* QuestDesc;
};
