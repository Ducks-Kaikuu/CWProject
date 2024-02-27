// Fill out your copyright notice in the Description page of Project Settings.


#include "Utility/SNUtility.h"

//----------------------------------------------------------------------//
//
//! @brief 非同期ロードのリクエスト処理
//
//! @param assetList           ロードするアセットのパスリスト
//! @param delegate            ロード終了時に呼ばれるデリゲート
//! @param priority            プライオリティ指定
//! @param bManageActiveHandle 
//! @param bStartStalled       
//! @param name                
//
//! @retval 非同期ロードハンドルへのポインタ
//
//----------------------------------------------------------------------//
TSharedPtr<FStreamableHandle> SNUtility::RequestAsyncLoad(TArray<FSoftObjectPath>& assetList, FStreamableDelegate delegate, TAsyncLoadPriority priority, bool bManageActiveHandle, bool bStartStalled, FString name){
	// アセットリストに何も登録されていない場合は終了
	if(assetList.Num() <= 0){
		return nullptr;
	}
	// ストリームマネージャーを取得
	FStreamableManager& Streamable = UAssetManager::GetStreamableManager();
	// ロードをリクエスト
	TSharedPtr<FStreamableHandle> handle(Streamable.RequestAsyncLoad(assetList, delegate, priority, bManageActiveHandle, bStartStalled, name));
	
	return handle;
}

