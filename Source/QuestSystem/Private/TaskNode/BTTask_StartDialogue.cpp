// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskNode/BTTask_StartDialogue.h"
#include "Component/PlayerHUDComponent.h"
#include "HUD/GameMainWidget.h"
#include "HUD/PlayerHUD.h"
#include "Kismet/GameplayStatics.h"

UBTTask_StartDialogue::UBTTask_StartDialogue()
{
	NodeName = TEXT("BT Start Dialogue");
}

EBTNodeResult::Type UBTTask_StartDialogue::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

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
	PlayerHUDComponent->ActivateDialogue(true);

	const auto GameMainWidget = PlayerHUDComponent->GetMainDisplay();
	if (!GameMainWidget) return EBTNodeResult::Failed;
	GameMainWidget->SetupDialogueText("");
	
	return EBTNodeResult::Succeeded;
}