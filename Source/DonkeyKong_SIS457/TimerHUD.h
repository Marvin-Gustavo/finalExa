// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TimerHUD.generated.h"

/**
 * 
 */
UCLASS()
class DONKEYKONG_SIS457_API ATimerHUD : public AHUD
{
	GENERATED_BODY()
public:
	void SetTiempoRestante(float Tiempo);

protected:
	virtual void DrawHUD();

private:
	float TiempoRestante;
	
};
