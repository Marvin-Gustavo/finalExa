// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "CanvasItem.h" 
void ATimerHUD::SetTiempoRestante(float Tiempo)
{
    TiempoRestante = Tiempo;
}

void ATimerHUD::DrawHUD()
{
    Super::DrawHUD();

    FString TiempoTexto = FString::Printf(TEXT("Tiempo: %.0f s"), TiempoRestante);
    FVector2D PosicionTexto(100, 100);  // Posición en pantalla

    FCanvasTextItem TextItem(PosicionTexto, FText::FromString(TiempoTexto), GEngine->GetMediumFont(), FLinearColor::White);
    TextItem.Scale = FVector2D(2.0f, 2.0f);
    Canvas->DrawItem(TextItem);

}


