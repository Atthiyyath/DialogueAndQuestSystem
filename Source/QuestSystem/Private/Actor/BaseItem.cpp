// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/BaseItem.h"
#include "Component/CollectibleItemComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

ABaseItem::ABaseItem()
{
	PrimaryActorTick.bCanEverTick = true;

	TriggerArea = CreateDefaultSubobject<USphereComponent>(TEXT("Collision Trigger"));
	TriggerArea->SetSphereRadius(200.f);
	TriggerArea->SetupAttachment(RootComponent);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	Mesh->SetupAttachment(TriggerArea);

	CollectibleItemComponent = CreateDefaultSubobject<UCollectibleItemComponent>(TEXT("Collectible Item Component"));
}

void ABaseItem::BeginPlay()
{
	Super::BeginPlay();

	TriggerArea->OnComponentBeginOverlap.AddDynamic(this, &ABaseItem::OnAreaBeginOverlap);
	TriggerArea->OnComponentEndOverlap.AddDynamic(this, &ABaseItem::OnAreaEndOverlap);

	Player = UGameplayStatics::GetPlayerCharacter(this, 0);
	if (!Player) return;
}

void ABaseItem::OnAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// override function!
}

void ABaseItem::OnAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// override function!
}