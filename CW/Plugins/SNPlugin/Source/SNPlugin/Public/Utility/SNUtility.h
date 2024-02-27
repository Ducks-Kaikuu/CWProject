// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Engine/AssetManager.h"

/**
 * 
 */
class SNPLUGIN_API SNUtility
{
public:
	 SNUtility() = delete;
	~SNUtility() = delete;
	
	//! @{@name 非同期ロードのリクエスト処理
	template<class T>
	static TSharedPtr<FStreamableHandle> RequestAsyncLoad(TArray<FSoftObjectPath>& assetList, T* pClass, typename TMemFunPtrType<false, T, void ()>::Type pFunc, TAsyncLoadPriority priority = FStreamableManager::DefaultAsyncLoadPriority, bool bManageActiveHandle = false, bool bStartStalled = false, FString name = TEXT("ArrayDelegate"));
	
	static TSharedPtr<FStreamableHandle> RequestAsyncLoad(TArray<FSoftObjectPath>& assetList, FStreamableDelegate delegate = FStreamableDelegate(), TAsyncLoadPriority priority = FStreamableManager::DefaultAsyncLoadPriority, bool bManageActiveHandle = false, bool bStartStalled = false, FString name = TEXT("ArrayDelegate"));
	//! @}
};

//----------------------------------------------------------------------//
//
//! @brief 非同期ロードのリクエスト処理
//
//! @param assetList            ロードするアセットのパスリスト
//! @param pClass               クラスへのポインタ
//! @param TMemFunPtrType<false ロード終了デリゲート
//
//! @retval 非同期ロードハンドルへのポインタ
//
//----------------------------------------------------------------------//
template<class T>
inline TSharedPtr<FStreamableHandle> SNUtility::RequestAsyncLoad(TArray<FSoftObjectPath>& assetList, T* pClass, typename TMemFunPtrType<false, T, void ()>::Type pFunc, TAsyncLoadPriority priority, bool bManageActiveHandle, bool bStartStalled, FString name){
	
	if((pClass != nullptr) && (pFunc != nullptr)){
		return RequestAsyncLoad(assetList, FStreamableDelegate::CreateUObject(pClass, pFunc), priority, bManageActiveHandle, bStartStalled, name);
	} else {
		return RequestAsyncLoad(assetList, FStreamableDelegate(), priority, bManageActiveHandle, bStartStalled, name);
	}
}
