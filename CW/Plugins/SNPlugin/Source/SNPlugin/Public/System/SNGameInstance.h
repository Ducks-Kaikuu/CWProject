// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SNGameInstance.generated.h"

class USNOnlineSystem;
class USNDataAssetManager;

/**
 * ゲームインスタンス
 */
UCLASS()
class SNPLUGIN_API USNGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	//! @{@name コンストラクタ
	USNGameInstance();
	//! @}
	
	//! @{@name 初期化処理
	virtual void Init() override ;
	//! @}
	
	//! @{@name データアセット管理クラスのポインタを取得
	USNDataAssetManager* GetDataAssetManager();
	//! @}
	
	//! @{@name オンラインシステムが有効かのチェック
	bool IsEnabledOnlineSystem() const ;
	//! @}
	
	//! @{@name オンラインシステムのインスタンスを取得
	USNOnlineSystem* GetOnlineSystem();
	//! @}
	
private:
	
	//!< データアセット管理クラス
	UPROPERTY(EditAnywhere, Category="Data")
	TSoftClassPtr<USNDataAssetManager> DataAssetManagerClass = nullptr;
	
	//!< オンラインシステムクラス(設定されていればオンラインシステムが有効になります)
	UPROPERTY(EditAnywhere, Category="Online")
	TSoftClassPtr<USNOnlineSystem> OnlineSystemClass = nullptr;
	
	//!< データアセット管理クラスのインスタンス
	UPROPERTY()
	TObjectPtr<USNDataAssetManager> DataAssetManager = nullptr;
	
	//!< オンラインシステムクラスのインスタンス
	UPROPERTY()
	TObjectPtr<USNOnlineSystem> OnlineSystem = nullptr;
};

//----------------------------------------------------------------------//
//
//! @brief データアセット管理クラスのポインタを取得
//
//! @retval データアセット管理クラスのポインタ
//
//----------------------------------------------------------------------//
FORCEINLINE USNDataAssetManager* USNGameInstance::GetDataAssetManager()
{
	return DataAssetManager;
}

//----------------------------------------------------------------------//
//
//! @brief オンラインシステムのインスタンスを取得
//
//! @retval オンラインシステムのインスタンス
//
//----------------------------------------------------------------------//
FORCEINLINE USNOnlineSystem* USNGameInstance::GetOnlineSystem()
{
	return OnlineSystem;
}


//----------------------------------------------------------------------//
//
//! @brief オンラインシステムが有効かのチェック
//
//! @retval true : オンラインシステム有効 / false : オンラインシステム無効
//
//----------------------------------------------------------------------//
FORCEINLINE bool USNGameInstance::IsEnabledOnlineSystem() const 
{
	return (OnlineSystem != nullptr) ? true : false;
} 
