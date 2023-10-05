// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/InteractableWidgetComponent.h"
#include "HUD/PanelInteractableWidget.h"

void UInteractableWidgetComponent::SetInteractActive(bool IsActive)
{
	PanelInteractableWidget = Cast<UPanelInteractableWidget>(GetUserWidgetObject());
	if (!PanelInteractableWidget) return;
	PanelInteractableWidget->SetVisibility(IsActive);
}
