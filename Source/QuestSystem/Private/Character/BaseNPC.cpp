// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BaseNPC.h"
#include "Character/QuestSystemCharacter.h"
#include "Components/SphereComponent.h"
#include "Component/SpeakerDialogueComponent.h"
#include "Component/SpeakerQuestComponent.h"
#include "Components/WidgetComponent.h"
#include "HUD/InteractableWidgetComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseNPC::ABaseNPC()
{
	ConversationArea = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Component"));
	ConversationArea->SetSphereRadius(200.f);
	ConversationArea->SetupAttachment(RootComponent);

	InteractableWidgetComp = CreateDefaultSubobject<UInteractableWidgetComponent>(TEXT("Interactable Widget Component"));
	InteractableWidgetComp->SetupAttachment(RootComponent);
	InteractableWidgetComp->SetRelativeLocation(FVector(0.0f, 0.0f, 110.f));
	InteractableWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);

	SpeakerDialogueComponent = CreateDefaultSubobject<USpeakerDialogueComponent>(TEXT("NPC Dialogue Component"));
	SpeakerQuestComponent = CreateDefaultSubobject<USpeakerQuestComponent>(TEXT("NPC Quest Component"));
}

void ABaseNPC::BeginPlay()
{
	Super::BeginPlay();

	ConversationArea->OnComponentBeginOverlap.AddDynamic(this, &ABaseNPC::OnAreaBeginOverlap);
	ConversationArea->OnComponentEndOverlap.AddDynamic(this, &ABaseNPC::OnAreaEndOverlap);

	InteractableWidgetComp->SetInteractActive(false);
	Player = UGameplayStatics::GetPlayerCharacter(this, 0);
}

void ABaseNPC::OnAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                  UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != Player) return;
	InteractableWidgetComp->SetInteractActive(true);
}

void ABaseNPC::OnAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
								UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != Player) return;	
	InteractableWidgetComp->SetInteractActive(false);
}

void ABaseNPC::OnInteract()
{
	// override function!
}
