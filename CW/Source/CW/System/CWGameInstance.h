// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/SNGameInstance.h"
#include "CWGameInstance.generated.h"

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
class UCWInputDataAsset;

/**
 * 
 */
UCLASS()
class CW_API UCWGameInstance : public USNGameInstance
{
	GENERATED_BODY()
	
public:
	
	//! @{@name 初期化処理
	virtual void Init() override ;
	//! @}
	
};

UCWGameInstance* GetCWGameInstance();
