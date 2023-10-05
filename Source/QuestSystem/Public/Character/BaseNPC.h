// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BaseCharacter.h"
#include "Interface/InteractableInterface.h"
#include "BaseNPC.generated.h"

UCLASS()
class QUESTSYSTEM_API ABaseNPC : public ABaseCharacter, public IInteractableInterface
{
	GENERATED_BODY()
	
public:
	ABaseNPC();

	// Interface Function
	virtual void OnInteract() override;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	virtual void OnAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(Category = NPC, VisibleAnywhere, BlueprintReadOnly)
	class USpeakerDialogueComponent* SpeakerDialogueComponent;

	UPROPERTY(Category = NPC, VisibleAnywhere, BlueprintReadOnly)
	class USpeakerQuestComponent* SpeakerQuestComponent;

	class ACharacter* Player;
	
private:
	UPROPERTY(Category = NPC, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInteractableWidgetComponent* InteractableWidgetComp;
	
	UPROPERTY(Category = NPC, EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* ConversationArea;

public:
	FORCEINLINE USpeakerDialogueComponent* GetSpeakerDialogueComponent() const {return SpeakerDialogueComponent;} ;
	FORCEINLINE USpeakerQuestComponent* GetSpeakerQuestComponent() const {return SpeakerQuestComponent;} ;
};
