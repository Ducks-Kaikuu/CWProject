// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Action/CWActionBase.h"
#include "CWVehicleShoot.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CW_API UCWVehicleShoot : public UCWActionBase
{
	GENERATED_BODY()

protected:
	
	void ExecAction(const FInputActionValue& InputActionValue) override;
};
