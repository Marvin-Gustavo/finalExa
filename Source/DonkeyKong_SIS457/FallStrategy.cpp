// Fill out your copyright notice in the Description page of Project Settings.


#include "FallStrategy.h"

// Sets default values
AFallStrategy::AFallStrategy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFallStrategy::CambiarHabilidad()
{
	// Lógica para caer (mover hacia abajo) 
	SetActorLocation(GetActorLocation() - FVector(0.f, 0.f, 1.f));
}

// Called when the game starts or when spawned
void AFallStrategy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFallStrategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

