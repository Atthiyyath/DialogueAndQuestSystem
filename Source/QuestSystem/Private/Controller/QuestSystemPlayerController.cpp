// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/QuestSystemPlayerController.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"
#include "Component/PlayerDialogueComponent.h"
#include "Component/PlayerHUDComponent.h"
#include "HUD/PlayerHUD.h"
#include "HUD/GameMainWidget.h"
#include "Kismet/GameplayStatics.h"

void AQuestSystemPlayerController::BeginPlay()
{
	Super::BeginPlay();

	Character = UGameplayStatics::GetPlayerCharacter(this, 0);
	PlayerDialogueComponent = Cast<UPlayerDialogueComponent>(Character->GetComponentByClass(UPlayerDialogueComponent::StaticClass()));
	if (!PlayerDialogueComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please add the PlayerDialogueComponent on PlayerCharacter first!"));
		return;
	}
	
	const AHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD();
	PlayerHUDComponent = Cast<UPlayerHUDComponent>(HUD->GetComponentByClass(UPlayerHUDComponent::StaticClass()));
	if (!PlayerHUDComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please assign the PlayerHUDComponent ActorComponent to your AHUD!"));
		return;
	}
}

void AQuestSystemPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &AQuestSystemPlayerController::Interact);
		EnhancedInputComponent->BindAction(QuestPanelAction, ETriggerEvent::Triggered, this, &AQuestSystemPlayerController::ShowQuestPanel);
	}
}

void AQuestSystemPlayerController::Interact()
{
	GameMainWidget = PlayerHUDComponent->GetMainDisplay();
	if (!GameMainWidget) return;

	if (GameMainWidget->GetDialogueActive() == false)
	{
		if (PlayerDialogueComponent->GetDialogueReady())
		{
			PlayerDialogueComponent->StartDialogue();
		}
	}
}

void AQuestSystemPlayerController::ShowQuestPanel()
{
	GameMainWidget = PlayerHUDComponent->GetMainDisplay();
	if (!GameMainWidget) return;

	if (GameMainWidget->GetDialogueActive() == false)
	{
		if (IsQuestActive)
		{
			GameMainWidget->PanelQuestVisibility(IsQuestActive);
			GameMainWidget->LockCharacter(true);
		}
		else
		{
			GameMainWidget->PanelQuestVisibility(IsQuestActive);
			GameMainWidget->LockCharacter(false);
		}
		IsQuestActive = !IsQuestActive;
	}
}
