// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PanelInteractableWidget.h"

void UPanelInteractableWidget::SetVisibility(bool IsActive) const
{
	const ESlateVisibility RenderValue = IsActive ? ESlateVisibility::Visible : ESlateVisibility::Hidden;
	PanelInteract->SetVisibility(RenderValue);
}
