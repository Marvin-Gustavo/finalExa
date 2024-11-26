// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyStrategy.h"

// Sets default values
AFlyStrategy::AFlyStrategy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFlyStrategy::CambiarHabilidad()
{
	// Lógica para volar (mover hacia arriba) 
	SetActorLocation(GetActorLocation() + FVector(0.f, 0.f, 1.f));
}

// Called when the game starts or when spawned
void AFlyStrategy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFlyStrategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

