// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Structure/QuestStructure.h"
#include "BTDecorator_CheckQuest.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UBTDecorator_CheckQuest : public UBTDecorator
{
	GENERATED_BODY()

public:
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;

	UPROPERTY(EditAnywhere, Category = Quest)
	EQuestState QuestState;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
