// Copyright Epic Games, Inc. All Rights Reserved.

#include "CW.h"
#include "CWDef.h"
#include "CW/System/CWBlueprintFunctionLibrary.h"
#include "System/SNGameInstance.h"
#include "Modules/ModuleManager.h"
#include "Kismet/GameplayStatics.h"

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
ACWPlayerController* GetPlayerController(){
	
	ACWPlayerController* pPlayerController = Cast<ACWPlayerController>(UGameplayStatics::GetGameInstance(GetPrimaryWorld())->GetPrimaryPlayerController());
	
	return pPlayerController;
}
