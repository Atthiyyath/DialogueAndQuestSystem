// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/PlayerHUD.h"
#include "Component/PlayerHUDComponent.h"

APlayerHUD::APlayerHUD()
{
	PlayerHUDComponent = CreateDefaultSubobject<UPlayerHUDComponent>(TEXT("PlayerHUD Component"));
}

