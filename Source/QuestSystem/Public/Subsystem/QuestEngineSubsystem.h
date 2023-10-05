// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Manager/QuestManager.h"
#include "Subsystems/EngineSubsystem.h"
#include "QuestEngineSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UQuestEngineSubsystem : public UEngineSubsystem
{
	GENERATED_BODY()

public:
	UQuestEngineSubsystem();

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	void SetQuestManager(UQuestManager* InQuestManager);
	void QuestData();

private:
	int32 IndexQuest;
	
	UPROPERTY()
	class UQuestManager* QuestManager;

public:
	FORCEINLINE UQuestManager* GetQuestManager();
};
