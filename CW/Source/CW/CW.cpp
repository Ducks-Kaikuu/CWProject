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
//! @brief CWGameInstance���擾
//
//! @retval CWGameInstance�ւ̃|�C���^
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
//! @brief CWPlayerController���擾
//
//! @retval CWPlayerController�ւ̃|�C���^
//
//----------------------------------------------------------------------//
ACWPlayerController* GetCWPlayerController(){
	
	ACWPlayerController* pPlayerController = Cast<ACWPlayerController>(UGameplayStatics::GetGameInstance(GetPrimaryWorld())->GetPrimaryPlayerController());
	
	return pPlayerController;
}
