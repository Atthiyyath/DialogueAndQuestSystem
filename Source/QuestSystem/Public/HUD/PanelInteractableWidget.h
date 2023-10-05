// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "PanelInteractableWidget.generated.h"

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UPanelInteractableWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetVisibility(bool IsActive) const;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class USizeBox> PanelInteract;
	
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	TObjectPtr<class UTextBlock> TextInteract;
};
