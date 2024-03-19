// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SNGameInstance.generated.h"

class USNInputConfig;
class USNOnlineSystem;
class USNDataAssetManager;
/**
 * 
 */
UCLASS()
class SNPLUGIN_API USNGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	USNGameInstance();
	
	//! @{@name 初期化処理
	virtual void Init() override ;
	//! @}
	
	//! @{@name データアセット管理クラスのポインタを取得
	USNDataAssetManager* GetDataAssetManager();
	//! @}

	bool StartOnlineSystem();

	bool IsEnabledOnlineSystem() const ;
	
	USNOnlineSystem* GetOnlineSystem();
	
private:
	
	//!< データアセット管理クラス
	UPROPERTY(EditAnywhere, Category="Data")
	TSoftClassPtr<USNDataAssetManager> DataAssetManagerClass = nullptr;

	// データアセット管理クラスのインスタンス
	UPROPERTY()
	TObjectPtr<USNDataAssetManager> DataAssetManager = nullptr;

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
FORCEINLINE USNDataAssetManager* USNGameInstance::GetDataAssetManager(){
	return DataAssetManager;
}

FORCEINLINE USNOnlineSystem* USNGameInstance::GetOnlineSystem()
{
	return OnlineSystem;
}


FORCEINLINE bool USNGameInstance::IsEnabledOnlineSystem() const {
	return (OnlineSystem != nullptr) ? true : false;
} 



