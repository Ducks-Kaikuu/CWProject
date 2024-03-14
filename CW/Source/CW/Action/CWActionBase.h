// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SNActionBase.h"
#include "CWActionBase.generated.h"

/**
 * 
 */
UCLASS()
class CW_API UCWActionBase : public USNActionBase
{
	GENERATED_BODY()
	
public:
	//! @{@name デフォルトコンストラクタ
	UCWActionBase();
	//! @}
	
	//! @{@name デストラクタ
	virtual ~UCWActionBase();
	//! @}
	
};
