// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PanelDialogue.generated.h"

class UListPlayerOption;

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UPanelDialogue : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetDialogueActive(bool IsVisible);
	void SetOptionActive(bool IsVisible) const;
	void SetupOption(TArray<FString> Options);
	void CloseOption();

	UFUNCTION(BlueprintCallable)
	void SetupDialogue(FString Dialogue);

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* DialogueText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	class UVerticalBox* PanelOption;

	UPROPERTY(BlueprintReadWrite)
	UListPlayerOption* ListPlayerOption;

private:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget),  meta = (AllowPrivateAccess = "true"))
	class USizeBox* DialogueBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UListPlayerOption> OptionWidget;

	UPROPERTY()
	TArray<UListPlayerOption*> ListOptions;
};
