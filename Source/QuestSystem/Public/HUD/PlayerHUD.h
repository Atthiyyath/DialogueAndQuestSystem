// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

class UPlayerHUDComponent;

/**
 * 
 */
UCLASS()
class QUESTSYSTEM_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	APlayerHUD();
	
private:
	UPROPERTY(Category = NPC, EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UPlayerHUDComponent* PlayerHUDComponent;
};
