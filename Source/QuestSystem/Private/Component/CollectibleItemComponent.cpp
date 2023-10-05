// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/CollectibleItemComponent.h"
#include "Character/QuestSystemCharacter.h"
#include "Component/PlayerQuestComponent.h"
#include "Kismet/GameplayStatics.h"

UCollectibleItemComponent::UCollectibleItemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UCollectibleItemComponent::BeginPlay()
{
	Super::BeginPlay();
	
	const ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	const auto PlayerQuestComponent = Cast<UPlayerQuestComponent>(Character->GetComponentByClass(UPlayerQuestComponent::StaticClass()));
	if (!PlayerQuestComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please add the PlayerQuestComponent on PlayerCharacter first!"));
		return;
	}
	
	OnCollectItem.AddDynamic(PlayerQuestComponent, &UPlayerQuestComponent::CheckIndex);
}

void UCollectibleItemComponent::CollectItem() const
{
	if (!OnCollectItem.IsBound()) return;
	OnCollectItem.Broadcast(IndexQuest);
}


