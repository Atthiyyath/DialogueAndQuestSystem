// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/CollectibleItem.h"
#include "Component/CollectibleItemComponent.h"
#include "Components/MeshComponent.h"

ACollectibleItem::ACollectibleItem()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ACollectibleItem::BeginPlay()
{
	Super::BeginPlay();

	
}

void ACollectibleItem::OnAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnAreaBeginOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor != Player) return;
	CollectibleItemComponent->CollectItem();
	this->Destroy();
}

void ACollectibleItem::OnAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnAreaEndOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex);
	
}

