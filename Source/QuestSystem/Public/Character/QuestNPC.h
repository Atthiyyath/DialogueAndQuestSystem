// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseNPC.h"
#include "QuestNPC.generated.h"

UCLASS()
class QUESTSYSTEM_API AQuestNPC : public ABaseNPC
{
	GENERATED_BODY()

public:
	AQuestNPC();

	virtual void OnInteract() override;

protected:
	virtual void BeginPlay() override;
	
	virtual void OnAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	class UPlayerDialogueComponent* PlayerDialogueComponent;
	class UPlayerQuestComponent* PlayerQuestComponent;
	
	void SetupDialogueComponent(bool IsActive, AActor* Speaker) const;
};
