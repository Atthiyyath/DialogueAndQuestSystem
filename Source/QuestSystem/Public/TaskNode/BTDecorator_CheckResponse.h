// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_CheckResponse.generated.h"

UCLASS()
class QUESTSYSTEM_API UBTDecorator_CheckResponse : public UBTDecorator
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Dialogue)
	FString Option;

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
