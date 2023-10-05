// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Subsystem/QuestEngineSubsystem.h"
#include "BaseQuestComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UBaseQuestComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBaseQuestComponent();

protected:
	virtual void BeginPlay() override;
	
	class UQuestEngineSubsystem* QuestSubsystem;
	class UQuestManager* QuestManager;
	class AQuestSystemPlayerController* PlayerController;
	class APlayerHUD* PlayerHUD;

	class UPlayerHUDComponent* PlayerHUDComponent;
	class UGameMainWidget* MainWidget;
	
public:
	virtual void QuestAvailability();
	virtual void QuestCompleted();

	UFUNCTION()
	virtual void CheckProgress(const TArray<int32>& ItemCollected);
	
};
