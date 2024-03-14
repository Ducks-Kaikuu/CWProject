// Copyright Epic Games, Inc. All Rights Reserved.

#include "CW.h"
#include "CWDef.h"
#include "CW/System/CWBlueprintFunctionLibrary.h"
#include "CW/System/CWGameInstance.h"
#include "CW/Player/CWPlayerController.h"
#include "Utility/SNUtility.h"

#include "Modules/ModuleManager.h"
#include "Vehicle/CWWheeledVehiclePawn.h"
#include "Input/SNInputManagerSubsystem.h"

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
	return SNUtility::GetGameInstance<UCWGameInstance>();
}

//----------------------------------------------------------------------//
//
//! @brief CWPlayerControllerを取得
//
//! @retval CWPlayerControllerへのポインタ
//
//----------------------------------------------------------------------//
ACWPlayerController* GetCWPlayerController(){
	return SNUtility::GetPlayerController<ACWPlayerController>();
}

//----------------------------------------------------------------------//
//
//! @brief 現在のプレイヤーへのポインタを取得
//
//! @retval 
//
//----------------------------------------------------------------------//
ACWWheeledVehiclePawn* GetCurrentPlayer(){
	return SNUtility::GetCurrentPlayer<ACWWheeledVehiclePawn>();
}

USNInputManagerSubsystem* GetCwInputManagerSubsystem()
{
	return GetCWGameInstance()->GetSubsystem<USNInputManagerSubsystem>();
}