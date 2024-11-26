// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Teleporter.generated.h"

UCLASS()
class DONKEYKONG_SIS457_API ATeleporter : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATeleporter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Componente de colisión
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Teleporter")
	class UBoxComponent* CollisionBox;

	// Destino del teletransportador
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Teleporter")
	FVector TeleportDestination;

	// Función de colisión
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
