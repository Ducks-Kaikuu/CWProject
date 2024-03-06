// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SNGameInstance.generated.h"

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
	
private:
	
	//!< データアセット管理クラス
	UPROPERTY(EditAnywhere, Category="Data")
	TSoftClassPtr<USNDataAssetManager> DataAssetManagerClass = nullptr;
	
	// データアセット管理クラスのインスタンス
	UPROPERTY()
	TObjectPtr<USNDataAssetManager> DataAssetManager = nullptr;
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



