// Fill out your copyright notice in the Description page of Project Settings.


#include "ReturnToOriginStrategy.h"

// Sets default values
AReturnToOriginStrategy::AReturnToOriginStrategy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AReturnToOriginStrategy::CambiarHabilidad()
{
	// Lógica para regresar al origen 
	SetActorLocation(FVector(0.f, 0.f, 0.f));
}

// Called when the game starts or when spawned
void AReturnToOriginStrategy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReturnToOriginStrategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

