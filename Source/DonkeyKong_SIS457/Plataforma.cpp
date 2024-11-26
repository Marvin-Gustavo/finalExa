// Fill out your copyright notice in the Description page of Project Settings.


#include "Plataforma.h"

APlataforma::APlataforma()
{
    PrimaryActorTick.bCanEverTick = true;
    ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("StaticMesh'/Game/Geometry/Meshes/uploads_files_4917076_picatinny_deck_l.uploads_files_4917076_picatinny_deck_l'"));

    meshPlataforma = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    meshPlataforma->SetStaticMesh(MeshAsset.Object);
    RootComponent = meshPlataforma;

    FVector NewScale(0.4f, 6.0f, 0.5f);
    SetActorScale3D(NewScale);

    // Inicializar los límites de movimiento en Y
    LimiteIzquierdo = 1780.0f;
    LimiteDerecho = -2180.0f;
}

void APlataforma::BeginPlay()
{
    Super::BeginPlay();
}

void APlataforma::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Actualizar la posición de la plataforma en el eje Y
    FVector NuevaPosicion = GetActorLocation() + (Velocidad * DeltaTime);
    SetActorLocation(NuevaPosicion);

    if (NuevaPosicion.Y > LimiteIzquierdo || NuevaPosicion.Y < LimiteDerecho)
    {
        Velocidad.Y *= -1;
    }
}

void APlataforma::AgregarMovimiento(FVector Movimiento)
{
    Velocidad = Movimiento;
}
