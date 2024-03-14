// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Action/CWActionBase.h"
#include "CWActionCursorUD.generated.h"

/**
 * 
 */
UCLASS()
class CW_API UCWActionCursorUD : public UCWActionBase
{
	GENERATED_BODY()

public:
	
	void ExecAction(const FInputActionValue& InputActionValue) override; 
};
