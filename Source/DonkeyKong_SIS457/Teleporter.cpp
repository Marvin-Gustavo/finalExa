// Fill out your copyright notice in the Description page of Project Settings.

#include "Teleporter.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
// Sets default values
ATeleporter::ATeleporter()
{
    PrimaryActorTick.bCanEverTick = true;
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetBoxExtent(FVector(100.f, 100.f, 10.f));
    RootComponent = CollisionBox;
    //1210,1896,204,
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter::OnOverlapBegin);
}


void ATeleporter::BeginPlay()
{
    Super::BeginPlay();
}


void ATeleporter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATeleporter::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor != this)
    {

        if (TeleportDestination != FVector::ZeroVector)
        {

            OtherActor->SetActorLocation(TeleportDestination);
        }
    }
}


