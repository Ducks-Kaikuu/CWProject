// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SNGameInstance.generated.h"

//! @{@name プライマリーワールドへのポインタを取得
SNPLUGIN_API UWorld* GetPrimaryWorld();
//! @}

/**
 * 
 */
UCLASS()
class SNPLUGIN_API USNGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
};


