// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IProjectileAdapter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FuegoProjectile.generated.h"

UCLASS()
class DONKEYKONG_SIS457_API AFuegoProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuegoProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Disparar();
	float tiempo = 5;
private:
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* MovementComponent;

		

};
