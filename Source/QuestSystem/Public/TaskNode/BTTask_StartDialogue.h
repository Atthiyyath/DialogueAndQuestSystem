// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_StartDialogue.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UBTTask_StartDialogue : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_StartDialogue();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
