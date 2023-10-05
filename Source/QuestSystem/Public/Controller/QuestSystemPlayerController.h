// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "QuestSystemPlayerController.generated.h"

class UInputAction;

UCLASS()
class QUESTSYSTEM_API AQuestSystemPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void Interact();
	void ShowQuestPanel();
	
protected:
	virtual void BeginPlay() override;

	virtual void SetupInputComponent();

private:
	class UPlayerDialogueComponent* PlayerDialogueComponent;
	class APlayerHUD* PlayerHUD;
	class UGameMainWidget* GameMainWidget;
	class UPlayerHUDComponent* PlayerHUDComponent;
	class ACharacter* Character;
	
	bool IsQuestActive = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> InteractAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> QuestPanelAction;
};
