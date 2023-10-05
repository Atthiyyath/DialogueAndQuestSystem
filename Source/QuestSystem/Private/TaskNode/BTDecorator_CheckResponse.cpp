// Fill out your copyright notice in the Description page of Project Settings.


#include "TaskNode/BTDecorator_CheckResponse.h"
#include "HUD/PlayerHUD.h"
#include "HUD/GameMainWidget.h"
#include "Component/PlayerHUDComponent.h"
#include "Kismet/GameplayStatics.h"

bool UBTDecorator_CheckResponse::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	const AHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD();
	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("AHUD is null"));
		return false;
	}
	const auto PlayerHUDComponent = Cast<UPlayerHUDComponent>(HUD->GetComponentByClass(UPlayerHUDComponent::StaticClass()));
	if (!PlayerHUDComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please assign the PlayerHUDComponent ActorComponent to your AHUD!"));
		return false;
	}

	const UGameMainWidget* GameMainWidget = PlayerHUDComponent->GetMainDisplay();
	if (!GameMainWidget) return false;

	const auto GetResponse = GameMainWidget->GetResponse();
	if (Option == GetResponse)
	{
		return true;
	}
	return false;
}
