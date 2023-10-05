// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"
#include "GameMainWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestActive, int32, QuestID);

UCLASS()
class QUESTSYSTEM_API UGameMainWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	// Dialogue Function
	void SetupDialogueActive(bool IsActive);
	void SetupDialogueText(FString Dialogue);
	void PlayCutscene() const;
	void ContinueDialogue();
	void EndDialogue();
	// Option Selection
	void StartOption(TArray<FString> Options);
	void ShowOption();
	void CloseOption();
	// Gameplay Mode
	void LockCharacter(bool IsOccupied);
	void GameMode(bool IsPlaying) const;
	// Quest Function
	void PanelQuestVisibility(bool IsVisible) const;
	void PanelObjectiveQuestVisibility(bool IsVisible) const;

	// Delegate Function
	UFUNCTION()
	void ChooseOption(FString Option);

	UFUNCTION()
	void SetupQuestActive(int32 QuestIndex);

	UFUNCTION()
	void QuestCompleted();

	// Delegate Variable
	UPROPERTY(BlueprintAssignable)
	FOnQuestActive OnQuestActive;
	
	UPROPERTY(EditAnywhere, Category = Quest)
	UDataTable* QuestDataTable;
	
private:
	UFUNCTION(BlueprintCallable)
	void InitWidget();

	// Bind Widget
	UPROPERTY(meta = (BindWidget))
	class UPanelDialogue* PanelDialogue;

	UPROPERTY(meta = (BindWidget))
	class UPanelQuestWidget* PlayerQuestWidget;

	UPROPERTY(meta = (BindWidget))
	class UPanelObjectivesQuestWidget* PanelObjectivesQuestWidget;

	// Local Variable
	class ACharacter* Player;
	class APlayerController* PlayerController;
	class UPlayerDialogueComponent* PlayerDialogueComponent;
	
	bool IsDialogueActive = false;
	bool IsDialogueFinished = false;
	bool IsOptionSelected = false;
	FString OptionSelected;

public:
	FORCEINLINE bool GetDialogueFinish(bool IsFinish) const { return IsFinish = IsDialogueFinished; }
	FORCEINLINE bool SetDialogueFinish(bool IsFinish) { return IsDialogueFinished = IsFinish; }
	FORCEINLINE bool GetOptionSelected(bool IsSelected) const { return IsSelected = IsOptionSelected; }
	FORCEINLINE FString GetResponse() const { return OptionSelected; }
	FORCEINLINE bool GetDialogueActive() const { return IsDialogueActive; }
};
