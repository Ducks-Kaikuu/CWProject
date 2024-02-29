// Copyright Epic Games, Inc. All Rights Reserved.

#include "CW.h"
#include "CWDef.h"
#include "CW/System/CWBlueprintFunctionLibrary.h"
#include "CW/System/CWGameInstance.h"
#include "CW/Player/CWPlayerController.h"

#include "Modules/ModuleManager.h"
#include "Kismet/GameplayStatics.h"
#include "Vehicle/CWWheeledVehiclePawn.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FDefaultGameModuleImpl, CW, "CW");

namespace CW{
void DebugPrintScreen(const FString& text, const FLinearColor& textColor, float screenX, float screenY, float duration, float scale){
	UCWBlueprintFunctionLibrary::DrawDisplay(text, textColor, screenX, screenY, duration, scale);
}
}

//----------------------------------------------------------------------//
//
//! @brief CWGameInstanceを取得
//
//! @retval CWGameInstanceへのポインタ
//
//----------------------------------------------------------------------//
UCWGameInstance* GetCWGameInstance(){
	
	if(UWorld* pPrimaryWorld = GetPrimaryWorld()){
		return Cast<UCWGameInstance>(pPrimaryWorld->GetGameInstance());
	}
	
	return nullptr;
}

//----------------------------------------------------------------------//
//
//! @brief CWPlayerControllerを取得
//
//! @retval CWPlayerControllerへのポインタ
//
//----------------------------------------------------------------------//
ACWPlayerController* GetCWPlayerController(){
	
	ACWPlayerController* pPlayerController = Cast<ACWPlayerController>(UGameplayStatics::GetGameInstance(GetPrimaryWorld())->GetPrimaryPlayerController());
	
	return pPlayerController;
}

ACWWheeledVehiclePawn* GetCurrentPlayer(){
	
	ACWWheeledVehiclePawn* Player = nullptr;
	
	ACWPlayerController* PlayerController = GetCWPlayerController();
	
	if(PlayerController != nullptr){
		Player = Cast<ACWWheeledVehiclePawn>(PlayerController->GetPawn());
	}
	
	return Player;	
}
