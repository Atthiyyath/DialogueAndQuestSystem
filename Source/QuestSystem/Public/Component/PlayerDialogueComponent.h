// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerDialogueComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UPlayerDialogueComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPlayerDialogueComponent();

	void OnEnterActor(AActor* OnInteractiveActor);
	void OnLeaveActor();
	void StartDialogue() const;
	void PlayCutsene();
	void StopCutscene();
	
protected:
	virtual void BeginPlay() override;
	
private:
	class AQuestNPC* NPC;
	class AActor* CurrentInteractiveActor;
	bool IsDialogueReady;
	
public:	
	FORCEINLINE bool GetDialogueReady() const { return IsDialogueReady; }
	FORCEINLINE void SetDialogueReady(bool IsReady) { IsDialogueReady = IsReady; }
};
