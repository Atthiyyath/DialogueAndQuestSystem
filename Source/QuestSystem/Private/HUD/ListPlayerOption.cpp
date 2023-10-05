// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/ListPlayerOption.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "HUD/PlayerHUD.h"
#include "Component/PlayerHUDComponent.h"
#include "HUD/GameMainWidget.h"
#include "Kismet/GameplayStatics.h"

void UListPlayerOption::SetupChoice(FString Value, int32 Index)
{
	OptionTxt->SetText(FText::FromString(Value));
	Option = Value;
}

void UListPlayerOption::SelectChoice()
{
	const AHUD* HUD = UGameplayStatics::GetPlayerController(this, 0)->GetHUD();
	if (!HUD)
	{
		UE_LOG(LogTemp, Warning, TEXT("AHUD is null"));
		return;
	}
	const auto PlayerHUDComponent = Cast<UPlayerHUDComponent>(HUD->GetComponentByClass(UPlayerHUDComponent::StaticClass()));
	if (!PlayerHUDComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please assign the PlayerHUDComponent ActorComponent to your AHUD!"));
		return;
	}

	const auto MainWidget = PlayerHUDComponent->GetMainDisplay();
	if (!MainWidget) return;
	OnOptionSelected.AddDynamic(MainWidget, &UGameMainWidget::ChooseOption);

	if (!OnOptionSelected.IsBound()) return;
	OnOptionSelected.Broadcast(Option);
}

void UListPlayerOption::HoverChoice(bool IsSelected)
{
	float IsSelectedValue = IsSelected ? 1.0f : 0.0f;
	BorderTop->SetRenderOpacity(IsSelectedValue);
	BorderBottom->SetRenderOpacity(IsSelectedValue);
}
