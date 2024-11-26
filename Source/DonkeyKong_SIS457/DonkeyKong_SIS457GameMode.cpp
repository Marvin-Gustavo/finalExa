// Copyright Epic Games, Inc. All Rights Reserved.

#include "DonkeyKong_SIS457GameMode.h"
#include "DonkeyKong_SIS457Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Plataforma.h"
#include "Teleporter.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "TimerManagerR.h"
#include "TimerHUD.h"
#include "Kismet/GameplayStatics.h"

ADonkeyKong_SIS457GameMode::ADonkeyKong_SIS457GameMode()
{
    // Set default pawn class to our Blueprinted character
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/SideScrollerCPP/Blueprints/SideScrollerCharacter"));
    if (PlayerPawnBPClass.Class != nullptr)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
    HUDClass = ATimerHUD::StaticClass();
}

void ADonkeyKong_SIS457GameMode::BeginPlay()
{
    Super::BeginPlay();

    GetWorld()->SpawnActor<ATimerManagerR>();
    // Instanciar el TimerManager
    ATimerManagerR* Timer = GetWorld()->SpawnActor<ATimerManagerR>();

    // Obtener el personaje y registrarlo como observador
    ADonkeyKong_SIS457Character* Character = Cast<ADonkeyKong_SIS457Character>(UGameplayStatics::GetPlayerCharacter(this, 0));
    if (Character && Timer)
    {
        // Establecer la posición objetivo para el personaje (por ejemplo, a (0, 0, 0))
        Character->SetPositionObjetivo(FVector(1208.0f, -517.0f, 205.0f));

        // Registrar el personaje como observador
        Timer->SetObservador(Character);
    }

    GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Blue, TEXT("Creando plataformas"));


    FVector posicionInicial = FVector(1160.0f, -1600.0f, 300.f);
    FRotator rotacionInicial = FRotator(0.0f, 0.0f, 10.0f);
    FTransform SpawnLocationCP;
    float anchoPlataforma = 600.0f;
    float incrementoAltoPlataforma = -105.0f;
    float incrementoAltoEntrePisos = 750.0f;
    float incrementoInicioPiso = 100.0f;

    // Crear plataformas y almacenarlas en el TMap
    for (int npp = 0; npp < 6; npp++) {
        if (npp % 2 == 0) {
            rotacionInicial.Roll = 0.0f;
        }
        else {
            rotacionInicial.Roll = 10.0f;
        }

        SpawnLocationCP.SetRotation(FQuat(rotacionInicial));
        int numPlataformas = (npp % 2 == 0) ? 1 : 5;

        for (int ncp = 0; ncp < numPlataformas; ncp++) {
            SpawnLocationCP.SetLocation(FVector(posicionInicial.X, posicionInicial.Y + anchoPlataforma * ncp, posicionInicial.Z));
            APlataforma* Plataforma = GetWorld()->SpawnActor<APlataforma>(APlataforma::StaticClass(), SpawnLocationCP);

            if (Plataforma) {
                // Almacenar la plataforma en el mapa con una clave única
                PlataformaMap.Add(npp * 10 + ncp, Plataforma);

                if (npp == 0 || npp == 2 || npp == 4) {
                    // Movimiento de izquierda a derecha
                    Plataforma->AgregarMovimiento(FVector(0.0f, 300.0f, 0.0f));
                }
            }

            if (ncp < numPlataformas - 1) {
                posicionInicial.Z = posicionInicial.Z + incrementoAltoPlataforma;
            }
        }

        posicionInicial.Z = posicionInicial.Z + incrementoAltoEntrePisos;
        posicionInicial.Y = posicionInicial.Y + incrementoInicioPiso;
    }

    FVector ubicacionesTeletransportadores[3] = {
         FVector(1210.0f, 1900.0f, 0.0f),
         FVector(1210.0f, -2310.0f, 0.0f),
         FVector(1210.0f, -1900.0f, 1040.0f)
    };

    FVector destinoTeletransporte = FVector(1210.0f, -1260.0f, 3470.0f);

    for (int i = 0; i < 3; i++)
    {
        FTransform teleporterTransform;
        teleporterTransform.SetLocation(ubicacionesTeletransportadores[i]);
        teleporterTransform.SetRotation(FQuat(FRotator::ZeroRotator));

        ATeleporter* LocalTeleporter = GetWorld()->SpawnActor<ATeleporter>(ATeleporter::StaticClass(), teleporterTransform);

        if (LocalTeleporter)
        {
            LocalTeleporter->TeleportDestination = destinoTeletransporte;

            TeletransportadorMap.Add(i, LocalTeleporter);

        }
    }
}
