// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/BaseQuestComponent.h"
#include "Component/PlayerHUDComponent.h"
#include "HUD/PlayerHUD.h"
#include "HUD/GameMainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Manager/QuestManager.h"

UBaseQuestComponent::UBaseQuestComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UBaseQuestComponent::BeginPlay()
{
	Super::BeginPlay();
	
	QuestSubsystem = GEngine->GetEngineSubsystem<UQuestEngineSubsystem>();
	QuestManager = QuestSubsystem->GetQuestManager();
	if (!QuestManager) return;

	const AHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD();
	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("AHUD is null"));
		return;
	}
	PlayerHUDComponent = Cast<UPlayerHUDComponent>(HUD->GetComponentByClass(UPlayerHUDComponent::StaticClass()));
	if (!PlayerHUDComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please assign the PlayerHUDComponent ActorComponent to your AHUD!"));
		return;
	}
}

void UBaseQuestComponent::QuestAvailability()
{
	// override function!
	
	MainWidget = PlayerHUDComponent->GetMainDisplay();
	if (!MainWidget) return;
}

void UBaseQuestComponent::QuestCompleted()
{
	// override function!
}

void UBaseQuestComponent::CheckProgress(const TArray<int32>& ItemCollected)
{
	// override function!
}
