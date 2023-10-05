// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/PlayerHUDComponent.h"
#include "HUD/GameMainWidget.h"
#include "Kismet/GameplayStatics.h"

UPlayerHUDComponent::UPlayerHUDComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPlayerHUDComponent::BeginPlay()
{
	Super::BeginPlay();

	PlayerController = UGameplayStatics::GetPlayerController(this, 0); 

	if (GetWorld() && PlayerController)
	{
		if (!MainWidgetClass) return;

		MainWidget = CreateWidget<UGameMainWidget>(PlayerController, MainWidgetClass);
		MainWidget->AddToViewport();
	}
}

void UPlayerHUDComponent::ActivateDialogue(bool IsActive) const
{
	if (!MainWidget) return;
	MainWidget->SetupDialogueActive(IsActive);
}

