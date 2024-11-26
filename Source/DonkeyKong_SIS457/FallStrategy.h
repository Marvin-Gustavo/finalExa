// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IStrategy.h"
#include "FallStrategy.generated.h"

UCLASS()
class DONKEYKONG_SIS457_API AFallStrategy : public AActor, public IIStrategy
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallStrategy();
	virtual void CambiarHabilidad() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
