// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Plataforma.generated.h"

UCLASS()
class DONKEYKONG_SIS457_API APlataforma : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APlataforma();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UStaticMeshComponent* meshPlataforma;

	// Velocidad de la plataforma
	UPROPERTY(EditAnywhere, Category = "Movimiento")
	FVector Velocidad;

	// Límites de movimiento
	UPROPERTY(EditAnywhere, Category = "Movimiento")
	float LimiteIzquierdo;

	UPROPERTY(EditAnywhere, Category = "Movimiento")
	float LimiteDerecho;


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Función para agregar movimiento
	void AgregarMovimiento(FVector Movimiento);
};