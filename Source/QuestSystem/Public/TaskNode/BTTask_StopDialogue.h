// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_StopDialogue.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNextDialogue, int32, Index);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnQuestIndex, int32, Index);

UENUM(BlueprintType)
enum class EDialogueType : uint8
{
	EDT_Quest		UMETA(Display = "Quest"),
	EDT_NonQuest	UMETA(Display = "Non Quest")
};

UENUM(BlueprintType)
enum class EQuestType : uint8
{
	EQT_SetAvailable	UMETA(Display = "Set Available"),
	EQT_SetCompleted	UMETA(Display = "Set Completed")
};

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API UBTTask_StopDialogue : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_StopDialogue();

	UPROPERTY(EditAnywhere, Category = Dialogue)
	EDialogueType DialogueType = EDialogueType::EDT_NonQuest;

	UPROPERTY(EditAnywhere, Category = Dialogue);
	int32 NewKey = 0;

	UPROPERTY(EditAnywhere, meta=(EditCondition="DialogueType==EDialogueType::EDT_Quest", EditConditionHides), Category = Quest)
	UDataTable* QuestDataTable;

	UPROPERTY(EditAnywhere, meta=(EditCondition="DialogueType==EDialogueType::EDT_Quest", EditConditionHides), Category = Quest)
	EQuestType QuestType = EQuestType::EQT_SetAvailable;
	
	UPROPERTY(BlueprintAssignable)
	FOnNextDialogue OnNextDialogue;

	UPROPERTY(BlueprintAssignable)
	FOnQuestIndex OnQuestIndex;

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	class AQuestSystemPlayerController* PlayerController;
	class APlayerHUD* PlayerHUD;
	class UPlayerHUDComponent* PlayerHUDComponent;
	class UGameMainWidget* GameMainWidget;
	class USpeakerQuestComponent* GetQuestSpeakerComponent;
	class UQuestManager* QuestManager;
};
