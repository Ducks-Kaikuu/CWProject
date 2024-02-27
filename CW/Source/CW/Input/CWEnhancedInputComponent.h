// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "CW/CWDef.h"
#include "CWEnhancedInputComponent.generated.h"

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
class UCWInputConfig;

/**
 * 
 */
UCLASS()
class CW_API UCWEnhancedInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
	
public:
	
	//! @{@name �f�t�H���g�R���X�g���N�^
	UCWEnhancedInputComponent(const FObjectInitializer& ObjectInitializer);
	//! @}

};
