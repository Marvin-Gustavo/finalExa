// Fill out your copyright notice in the Description page of Project Settings.


#include "ImmobileStrategy.h"

// Sets default values
AImmobileStrategy::AImmobileStrategy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AImmobileStrategy::CambiarHabilidad()
{
	//no se mueve
}

// Called when the game starts or when spawned
void AImmobileStrategy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AImmobileStrategy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

