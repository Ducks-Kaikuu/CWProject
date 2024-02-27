// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Action/CWActionBase.h"
#include "CWCameraOperation.generated.h"

/**
 * 
 */
UCLASS()
class CW_API UCWCameraOperation : public UCWActionBase
{
	GENERATED_BODY()
public:
	//! @{@name アクションの実行
	void ExecAction(const FInputActionValue& InputActionValue) override ;
	//! @}
};
