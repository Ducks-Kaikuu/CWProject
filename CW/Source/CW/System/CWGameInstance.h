// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Weapon/CWWeaponManager.h"
#include "System/SNGameInstance.h"
#include "CWGameInstance.generated.h"

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
class UCWMasterWidget;
class ACWSceneBase;

//----------------------------------------------------------------------//
//
//! @brief ゲームインスタンス
//
//----------------------------------------------------------------------//
UCLASS()
class CW_API UCWGameInstance : public USNGameInstance
{
	GENERATED_BODY()
	
public:
	
	//! @{@name 初期化処理
	virtual void Init() override ;
	//! @}
	
	//! @{@name 武器管理クラスを取得
	UCWWeaponManager* GetWeaponManager();
	//! @}

	void SetCurrentScene(ACWSceneBase* Scene);

	ACWSceneBase* GetCurrentScene();
	
private:
	//!< 武器管理クラス
	UPROPERTY()
	TObjectPtr<UCWWeaponManager> WeaponManager = nullptr;

	UPROPERTY()
	TObjectPtr<ACWSceneBase> CurrentScene = nullptr;
};

//----------------------------------------------------------------------//
//
//! @brief 武器管理クラスを取得
//
//! @retval 武器管理クラスへのポインタ
//
//----------------------------------------------------------------------//
FORCEINLINE UCWWeaponManager* UCWGameInstance::GetWeaponManager(){
	return WeaponManager;
}

FORCEINLINE ACWSceneBase* UCWGameInstance::GetCurrentScene()
{
	return CurrentScene;
}


UCWGameInstance* GetCWGameInstance();
