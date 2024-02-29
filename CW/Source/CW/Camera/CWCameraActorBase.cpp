// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Camera/CWCameraActorBase.h"

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//! @param ObjectInitializer イニシャライザ
//
//----------------------------------------------------------------------//
ACWCameraActorBase::ACWCameraActorBase(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}
