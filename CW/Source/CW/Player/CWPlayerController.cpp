// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Player/CWPlayerController.h"
#include "CW/CWDef.h"

#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "CW/System/CWGameInstance.h"
#include "Input/SNInputManagerSubsystem.h"

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//! @param ObjectInitializer イニシャライザ
//
//----------------------------------------------------------------------//
ACWPlayerController::ACWPlayerController(const FObjectInitializer& ObjectInitializer){
	
}

void ACWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	GetCWGameInstance()->StartOnlineSystem();
}
