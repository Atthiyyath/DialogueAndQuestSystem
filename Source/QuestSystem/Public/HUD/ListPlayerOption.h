// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ListPlayerOption.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOptionSelected, FString, Index);

class UImage;

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UListPlayerOption : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupChoice(FString Value, int32 Index);

	UFUNCTION(BlueprintCallable)
	void SelectChoice();

	UFUNCTION(BlueprintCallable)
	void HoverChoice(bool IsSelected);

	UPROPERTY(BlueprintReadOnly)
	FString Option;

	// Delegate variable
	UPROPERTY(BlueprintAssignable)
	FOnOptionSelected OnOptionSelected;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* OptionTxt;

	UPROPERTY(meta = (BindWidget))
	UImage* BorderTop;

	UPROPERTY(meta = (BindWidget))
	UImage* BorderBottom;
};
