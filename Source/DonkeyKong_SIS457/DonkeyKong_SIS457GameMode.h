// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DonkeyKong_SIS457GameMode.generated.h"
class APlataforma;
class ATeleporter;

UCLASS(minimalapi)
class ADonkeyKong_SIS457GameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ADonkeyKong_SIS457GameMode();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TMap<int32, APlataforma*> PlataformaMap;

    UPROPERTY()
    TMap<int32, ATeleporter*> TeletransportadorMap;

};