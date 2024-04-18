// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/SNGameState.h"
#include "CWGameState.generated.h"

/**
 * 
 */
UCLASS()
class CW_API ACWGameState : public ASNGameState
{
	GENERATED_BODY()

public:
	
	bool IsReadyToBattle() const ;

	int GetReadyToBattleCount() const ;
};
