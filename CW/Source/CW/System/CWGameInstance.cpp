// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/System/CWGameInstance.h"

#include "ModuleDescriptor.h"
#include "CW/CWDef.h"
#include "GameplayTags/SNGameplayTags.h"

#include "Components/GameFrameworkComponentManager.h"
#include "Modules/ModuleManifest.h"
#include "System/SNDLCModuleInterface.h"

//----------------------------------------------------------------------//
//
//! @brief 初期化処理
//
//----------------------------------------------------------------------//
void UCWGameInstance::Init(){
	
	Super::Init();
	
	WeaponManager = NewObject<UCWWeaponManager>();
	
	CW_ASSERT(WeaponManager != nullptr, TEXT("Failed to Create WeaponManager"));
}
