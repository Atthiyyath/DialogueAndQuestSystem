// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SpeakerDialogueComponent.generated.h"

class UPlayerDialogueComponent;
class ULevelSequence;
class ALevelSequenceActor;
class UBehaviorTree;
class ADialogueController;

USTRUCT(BlueprintType)
struct FDialogueData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditInstanceOnly, Category = Dialogue)
	class AActor* ActorPosition;

	UPROPERTY(EditInstanceOnly, Category = Dialogue)
	ULevelSequence* Cutscene;

	UPROPERTY(EditInstanceOnly, Category = Dialogue)
	UBehaviorTree* DialogueTree;

	UPROPERTY(VisibleAnywhere, Category = Dialogue)
	bool IsActive = false;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API USpeakerDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USpeakerDialogueComponent();

protected:
	virtual void BeginPlay() override;

public:	
	void SetupSequencer(UPlayerDialogueComponent* PlayerDialogueComponent);
	void SetupDialogueTree();
	void StopDialogueTree();
	void PlayCutscene() const;

	UFUNCTION(BlueprintCallable)
	void UpdateDialogue();

	UFUNCTION(BlueprintCallable)
	void StopCutscene();

	// Delegates function
	UFUNCTION()
	void OnNextDialogue(int32 InNextIndex);
	
private:
	class UPlayerHUDComponent* PlayerHUDComponent;
	
	UPROPERTY()
	ALevelSequenceActor* SequenceActor = nullptr;
	ADialogueController* DialogueController;

	UPROPERTY(EditInstanceOnly, Category = Dialogue)
	TMap<int32, FDialogueData> DialogueData;

	UPROPERTY(Category = Dialogue, VisibleAnywhere)
	int32 NextIndex = 0;
};
