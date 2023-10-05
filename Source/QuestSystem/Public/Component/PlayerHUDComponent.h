// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerHUDComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UPlayerHUDComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPlayerHUDComponent();

protected:
	virtual void BeginPlay() override;

public:	
	void ActivateDialogue(bool IsActive) const;

private:
	//class AQuestSystemPlayerController* PlayerController;
	class APlayerController* PlayerController;

	UPROPERTY()
	class UGameMainWidget* MainWidget;

	UPROPERTY(EditDefaultsOnly, Category = HUD)
	TSubclassOf <UGameMainWidget> MainWidgetClass;

public:
	FORCEINLINE UGameMainWidget* GetMainDisplay() const { return MainWidget; }
};
