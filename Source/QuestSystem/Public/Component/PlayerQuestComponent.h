// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseQuestComponent.h"
#include "Components/ActorComponent.h"
#include "PlayerQuestComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAddCollectibleItems, const TArray<int32>&, Index);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class QUESTSYSTEM_API UPlayerQuestComponent : public UBaseQuestComponent
{
	GENERATED_BODY()

public:	
	UPlayerQuestComponent();

protected:
	virtual void BeginPlay() override;

public:	
	UFUNCTION()
	void CheckIndex(int32 Index);
	
	void OnEnterActor(AActor* OnInteractiveActor);
	void OnLeaveActor();

	UPROPERTY(BlueprintAssignable)
	FOnAddCollectibleItems OnAddCollectibleItems;
	
	UPROPERTY(VisibleInstanceOnly, Category = Quest)
	TArray<int32> CollectibleItem;
	
private:
	int32 ItemID = 0;
	AActor* CurrentInteractiveActor;
};
