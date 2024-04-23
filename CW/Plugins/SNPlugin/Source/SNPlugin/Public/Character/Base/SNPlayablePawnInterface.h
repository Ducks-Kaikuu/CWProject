// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SNPlayablePawnInterface.generated.h"

class  USNActionBase;
struct FInputActionValue;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USNPlayablePawnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class SNPLUGIN_API ISNPlayablePawnInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
	ISNPlayablePawnInterface();

	virtual void AddInputAction(const FName& Name, USNActionBase* Action) = 0;

	virtual USNActionBase* GetAction(const FName& Name) = 0;

	virtual void ExecuteActionOnServer(const FName& Name, const FInputActionValue& InputActionValue) = 0;

protected:
	
	void ExecuteAction(const FName& Name, const FInputActionValue& InputActionValue);
};
