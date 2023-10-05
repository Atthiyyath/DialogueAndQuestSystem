// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DialogueController.generated.h"

UCLASS()
class QUESTSYSTEM_API ADialogueController : public AAIController
{
	GENERATED_BODY()

public:
	ADialogueController();

	virtual void OnPossess(APawn* InPawn) override;

	void StopBehaviourTree();

private:
	UPROPERTY(BlueprintReadWrite, Category = "AI Behaviour", meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* BlackboardComponent;

	UPROPERTY(BlueprintReadWrite, Category = "AI Behaviour", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTreeComponent* BehaviorTreeComponent;
};
