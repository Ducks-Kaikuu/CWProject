// Fill out your copyright notice in the Description page of Project Settings.

#include "CW/System/CWBlueprintFunctionLibrary.h"
#include "CW/CWDef.h"
#include "Utility/SNUtility.h"
#include "CW/UI/HUD/CWHUD.h"

#include "Kismet/GameplayStatics.h"

void UCWBlueprintFunctionLibrary::DrawDisplay(const FString& text, FLinearColor color, float screenX, float screenY, float lifeTime, float scale){
#if CW_DEBUG
	
	APlayerController* pPC = UGameplayStatics::GetPlayerController(SNUtility::GetWorld(), 0);
	// nullチェック
	if(pPC != nullptr){
		// HUDを取得
		ACWHUD* pHud = Cast<ACWHUD>(pPC->GetHUD());
		
		if(pHud != nullptr){
			// デバッグ文字列を表示
			pHud->DrawString(text, color, screenX, screenY, lifeTime, nullptr, scale, false);
		}
	}
#endif
}
