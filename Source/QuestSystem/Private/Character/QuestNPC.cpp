// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/QuestNPC.h"
#include "Character/QuestSystemCharacter.h"
#include "Component/PlayerDialogueComponent.h"
#include "Component/PlayerQuestComponent.h"
#include "Component/SpeakerDialogueComponent.h"
#include "Kismet/GameplayStatics.h"

AQuestNPC::AQuestNPC()
{
}

void AQuestNPC::BeginPlay()
{
	Super::BeginPlay();

	const ACharacter* Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (!Character) return;
	PlayerDialogueComponent = Cast<UPlayerDialogueComponent>(Character->GetComponentByClass(UPlayerDialogueComponent::StaticClass()));
	if (!PlayerDialogueComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please add the PlayerDialogueComponent on PlayerCharacter first!"));
		return;
	}
	
	PlayerQuestComponent = Cast<UPlayerQuestComponent>(Character->GetComponentByClass(UPlayerQuestComponent::StaticClass()));
	if (!PlayerQuestComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please add the PlayerQuestComponent on PlayerCharacter first!"));
		return;
	}
}

void AQuestNPC::OnAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnAreaBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	
	SetupDialogueComponent(true, this);
}

void AQuestNPC::OnAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnAreaEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	
	SetupDialogueComponent(false, nullptr);
	
	PlayerDialogueComponent->OnLeaveActor();
	PlayerQuestComponent->OnLeaveActor();
}

void AQuestNPC::OnInteract()
{
	Super::OnInteract();

	SpeakerDialogueComponent->SetupSequencer(PlayerDialogueComponent);
	SpeakerDialogueComponent->SetupDialogueTree();
}

void AQuestNPC::SetupDialogueComponent(bool IsActive, AActor* Speaker) const
{	
	PlayerDialogueComponent->SetDialogueReady(IsActive);
	PlayerDialogueComponent->OnEnterActor(Speaker);
	PlayerQuestComponent->OnEnterActor(Speaker);
}
