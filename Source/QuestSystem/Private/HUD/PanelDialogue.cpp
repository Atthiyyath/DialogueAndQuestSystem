// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PanelDialogue.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "HUD/ListPlayerOption.h"

void UPanelDialogue::SetDialogueActive(bool IsVisible)
{
	const ESlateVisibility RenderValue = IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	DialogueText->SetVisibility(RenderValue);
	DialogueBox->SetVisibility(RenderValue);
	PanelOption->SetVisibility(ESlateVisibility::Hidden);
}

void UPanelDialogue::SetupDialogue(FString Dialogue)
{
	DialogueText->SetText(FText::FromString(Dialogue));
}

void UPanelDialogue::SetOptionActive(bool IsVisible) const
{
	const ESlateVisibility RenderValue = IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	PanelOption->SetVisibility(RenderValue);
	PanelOption->SetRenderOpacity(1.0f);
}

void UPanelDialogue::SetupOption(TArray<FString> Options)
{
	int32 IndexBtn = 1;
	
	for (const FString Option : Options)
	{
		ListPlayerOption = CreateWidget<UListPlayerOption>(this, OptionWidget);
		ListPlayerOption->SetupChoice(Option, IndexBtn);
		ListPlayerOption->HoverChoice(false);
		PanelOption->AddChild(ListPlayerOption);
		ListOptions.Add(ListPlayerOption);
		IndexBtn++;
	}
}

void UPanelDialogue::CloseOption()
{
	PanelOption->SetRenderOpacity(0.0f);
	for (int i = 0; i < ListOptions.Num(); i++)
	{
		if (PanelOption->GetChildrenCount() > 0)
		{
			ListOptions[i]->RemoveFromParent();
		}
	}

	ListOptions.Empty();	
}
