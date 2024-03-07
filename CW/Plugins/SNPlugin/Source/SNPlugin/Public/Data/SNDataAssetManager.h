// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "System/SNGameInstance.h"
#include "SNDataAssetManager.generated.h"

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
class USNContentsAsset;

//----------------------------------------------------------------------//
//
//! @brief アセット管理クラス
//
//----------------------------------------------------------------------//
UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class SNPLUGIN_API USNDataAssetManager : public UObject
{
	GENERATED_BODY()

public:
	
	//! @{@name アセットリストを取得
	const TMap<FName, TObjectPtr<USNContentsAsset>>& GetAssetList() const ;
	//! @}
	
	//! @{@name コンテンツのアセットを取得
	const USNContentsAsset* GetContentAsset(FName Key) const ;
	//! @}
	
private:
	
	friend USNGameInstance;
	
	//! @{@name DLCコンテンツの初期化処理
	bool SetupDLCContents();
	//! @}
	
	//!< アセットリスト
	UPROPERTY(EditAnyWhere, Category="Data")
	TMap<FName, TObjectPtr<USNContentsAsset>> DataAssetList;
};

//----------------------------------------------------------------------//
//
//! @brief アセットリストを取得
//
//! @retval アセットリスト
//
//----------------------------------------------------------------------//
FORCEINLINE const TMap<FName, TObjectPtr<USNContentsAsset>>& USNDataAssetManager::GetAssetList() const {
	return DataAssetList;
}

