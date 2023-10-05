// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "InteractableWidgetComponent.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UInteractableWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	void SetInteractActive(bool IsActive);

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly)
	class UPanelInteractableWidget* PanelInteractableWidget;
};
