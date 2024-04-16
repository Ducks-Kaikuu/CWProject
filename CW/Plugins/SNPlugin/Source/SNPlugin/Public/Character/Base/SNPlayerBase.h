﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Base/SNCharacterBase.h"
#include "SNPlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class SNPLUGIN_API ASNPlayerBase : public ASNCharacterBase
{
	GENERATED_BODY()
	
protected:
	
	//! @{@name プレイヤーインプットコンポーネントの初期化
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//! @}
};