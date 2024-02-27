// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CWPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CW_API ACWPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	
	//! @{@name デフォルトコンストラクタ
	ACWPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	//! @}
	
};
