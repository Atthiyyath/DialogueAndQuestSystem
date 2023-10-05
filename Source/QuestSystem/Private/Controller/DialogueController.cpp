// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/DialogueController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ADialogueController::ADialogueController()
{
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardCOmponent"));
	check(BlackboardComponent);

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	check(BehaviorTreeComponent);
}

void ADialogueController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (!InPawn) return;
}

void ADialogueController::StopBehaviourTree()
{
	if (BehaviorTreeComponent && BehaviorTreeComponent->IsRunning())
	{
		BehaviorTreeComponent->StopTree();
	}
}