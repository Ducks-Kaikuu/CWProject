// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/System/CWGameInstance.h"

#include "CW/CWDef.h"
#include "CW/Scene/CWSceneBase.h"
#include "Kismet/GameplayStatics.h"

//----------------------------------------------------------------------//
//
//! @brief 初期化処理
//
//----------------------------------------------------------------------//
void UCWGameInstance::Init(){
	
	Super::Init();
	
	WeaponManager = NewObject<UCWWeaponManager>();
	
	CW_ASSERT(WeaponManager != nullptr, TEXT("Failed to Create WeaponManager"));

	WeaponManager->SetupWeaponDataAsset();
}

void UCWGameInstance::SetCurrentScene(ACWSceneBase* Scene)
{
	if((CurrentScene != nullptr) && (CurrentScene != Scene))
	{
		CurrentScene->Destroy();
	}

	CurrentScene = Scene;
}
