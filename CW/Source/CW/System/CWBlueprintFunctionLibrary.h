// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CWBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class CW_API UCWBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	//! @{@name デバッグ文字を画面上に表示
	static void DrawDisplay(const FString& text, FLinearColor color, float screenX, float screenY, float lifeTime = 0.0f, float scale = 1.0f);
	//! @}
};
