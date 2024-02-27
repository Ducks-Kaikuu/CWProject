// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Action/CWActionBase.h"
#include "CWVehicleSteer.generated.h"

/**
 * 
 */
UCLASS()
class CW_API UCWVehicleSteer : public UCWActionBase
{
	GENERATED_BODY()
	
protected:
	
	//! @{@name アクションの実行
	void ExecAction(const FInputActionValue& InputActionValue) override ;
	//! @}
};
