// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CollectibleItemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCollectItem, int32, Index);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class QUESTSYSTEM_API UCollectibleItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UCollectibleItemComponent();

	void CollectItem() const;

	UPROPERTY(EditInstanceOnly, Category = Item)
	int32 IndexQuest = 0;

	UPROPERTY(BlueprintAssignable)
	FOnCollectItem OnCollectItem;

protected:
	virtual void BeginPlay() override;

private:
	class AQuestSystemCharacter* Player;
};
