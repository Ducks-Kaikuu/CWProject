// Copyright Epic Games, Inc. All Rights Reserved.

#include "CW.h"
#include "CWDef.h"
#include "Modules/ModuleManager.h"
#include "CW/System/CWBlueprintFunctionLibrary.h"

IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, CW, "CW" );

namespace CW{
void DebugPrintScreen(const FString& text, const FLinearColor& textColor, float screenX, float screenY, float duration, float scale){
	UCWBlueprintFunctionLibrary::DrawDisplay(text, textColor, screenX, screenY, duration, scale);
}
}
