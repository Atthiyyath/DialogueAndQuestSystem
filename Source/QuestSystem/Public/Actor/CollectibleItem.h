// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "GameFramework/Actor.h"
#include "CollectibleItem.generated.h"

UCLASS()
class QUESTSYSTEM_API ACollectibleItem : public ABaseItem
{
	GENERATED_BODY()
	
public:	
	ACollectibleItem();

protected:
	virtual void BeginPlay() override;

	virtual void OnAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	
public:
	UPROPERTY(EditInstanceOnly, Category = Quest)
	int32 QuestIndex = 0;
};
