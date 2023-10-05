// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Structure/QuestStructure.h"
#include "BTTask_QuestAccessibility.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UBTTask_QuestAccessibility : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_QuestAccessibility();

	UPROPERTY(EditAnywhere, Category = Quest);
	int32 ThisQuestID = 0;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	class AQuestSystemPlayerController* PlayerController;
	class APlayerHUD* PlayerHUD;
	class UPlayerHUDComponent* PlayerHUDComp;
	class UGameMainWidget* MainWidget;
	class USpeakerQuestComponent* GetQuestSpeakerComponent;
	class UQuestManager* QuestManager;

	UPROPERTY(VisibleInstanceOnly, Category = Quest)
	EQuestState QuestState = EQuestState::EQS_Unavailable;
};
