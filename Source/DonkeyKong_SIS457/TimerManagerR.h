#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ITimerObserver.h"
#include "TimerManagerR.generated.h"

UCLASS()
class DONKEYKONG_SIS457_API ATimerManagerR : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATimerManagerR();

protected:
	// Called when the game starts or when spawned
	virtual void Tick(float DeltaTime);
private:
	float TiempoRestante;
	void ResetCronometro();

	IITimerObserver* Observador;

public:	
	void SetObservador(IITimerObserver* NuevoObservador);  // Método para registrar el observador
};
