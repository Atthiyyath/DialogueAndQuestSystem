// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DisplayResponse.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UBTTask_DisplayResponse : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_DisplayResponse();

	UPROPERTY(EditAnywhere, Category = Dialogue);
	FString Dialogue;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	class AQuestSystemPlayerController* PlayerController;
	class APlayerHUD* PlayerHUD;
	class UGameMainWidget* GameMainWidget;
};
