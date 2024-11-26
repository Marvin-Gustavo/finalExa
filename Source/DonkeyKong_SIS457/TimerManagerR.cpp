// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerManagerR.h"
#include "Kismet/GameplayStatics.h"
#include "TimerHUD.h"

// Sets default values
ATimerManagerR::ATimerManagerR()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TiempoRestante = 10.0f;
	Observador = nullptr;  // Inicializar sin observador
}

void ATimerManagerR::Tick(float DeltaTime)
{
    AActor::Tick(DeltaTime);  // Cambiar Super::Tick(DeltaTime) a AActor::Tick(DeltaTime)

    TiempoRestante -= DeltaTime;
    if (TiempoRestante <= 0.0f)
    {
        ResetCronometro();
        if (Observador)
        {
            Observador->OnTimerReachedZero();  // Notificar al observador si existe
        }
    }

    // Actualizar el HUD
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    if (PlayerController)
    {
        ATimerHUD* TimerHUD = Cast<ATimerHUD>(PlayerController->GetHUD());
        if (TimerHUD)
        {
            TimerHUD->SetTiempoRestante(TiempoRestante);
        }
    }
}

void ATimerManagerR::ResetCronometro()
{
    TiempoRestante = 10.0f;
}

void ATimerManagerR::SetObservador(IITimerObserver* NuevoObservador)
{
    Observador = NuevoObservador;  // Registra el observador
}


