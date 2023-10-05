// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskNode/BTTask_DisplayResponse.h"
#include "HUD/PlayerHUD.h"
#include "Component/PlayerHUDComponent.h"
#include "HUD/GameMainWidget.h"
#include "Kismet/GameplayStatics.h"

UBTTask_DisplayResponse::UBTTask_DisplayResponse()
{
	NodeName = TEXT("BT Display Response");
}

EBTNodeResult::Type UBTTask_DisplayResponse::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	bNotifyTick = true;

	if (!OwnerComp.GetOwner()) return EBTNodeResult::Failed;

	const AHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD();
	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("AHUD is null"));
		return EBTNodeResult::Failed;
	}
	const auto PlayerHUDComponent = Cast<UPlayerHUDComponent>(HUD->GetComponentByClass(UPlayerHUDComponent::StaticClass()));
	if (!PlayerHUDComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please assign the PlayerHUDComponent ActorComponent to your AHUD!"));
		return EBTNodeResult::Failed;
	}

	GameMainWidget = PlayerHUDComponent->GetMainDisplay();
	if (!GameMainWidget) return EBTNodeResult::Failed;
	
	return EBTNodeResult::InProgress;
}

void UBTTask_DisplayResponse::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!OwnerComp.GetOwner()) return;

	GameMainWidget->SetupDialogueText(Dialogue);
	GameMainWidget->PlayCutscene();
	if (GameMainWidget->GetDialogueFinish(true))
	{
		GameMainWidget->ContinueDialogue();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		
	}
}
