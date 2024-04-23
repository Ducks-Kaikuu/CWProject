// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Base/SNPlayablePawnInterface.h"

#include "Action/SNActionBase.h"

// Add default functionality here for any ISNPlayablePawnInterface functions that are not pure virtual.

ISNPlayablePawnInterface::ISNPlayablePawnInterface()
{
	
}

void ISNPlayablePawnInterface::ExecuteAction(const FName& Name, const FInputActionValue& InputActionValue)
{
	USNActionBase* Action(GetAction(Name));

	if(Action == nullptr)
	{
		return;
	}

	Action->ExecAction(InputActionValue);
}




