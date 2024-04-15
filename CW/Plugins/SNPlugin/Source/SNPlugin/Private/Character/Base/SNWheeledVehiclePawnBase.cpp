// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Base/SNWheeledVehiclePawnBase.h"

#include "SNDef.h"
#include "Character/SNPlayerController.h"
#include "Character/Base/SNWheeledVehiclePlayerBase.h"
#include "Utility/SNUtility.h"

void ASNWheeledVehiclePlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	ASNPlayerController* PlayerController(SNUtility::GetPlayerController<ASNPlayerController>());

	if(PlayerController != nullptr)
	{
		PlayerController->InitializeInput();

		SNPLUGIN_LOG(TEXT("Setup Player Input Component."));
	}
}
