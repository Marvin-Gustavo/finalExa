// Fill out your copyright notice in the Description page of Project Settings.


#include "StrategyFire.h"

// Sets default values
AStrategyFire::AStrategyFire()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStrategyFire::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AStrategyFire::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStrategyFire::CambiarHabilidad()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Magenta,
		FString::Printf(TEXT("Habilidad: Doble Salto")));
}

