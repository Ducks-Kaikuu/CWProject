// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Weapon/CWWeaponManager.h"
#include "CW/CWDef.h"
#include "CW/System/CWGameInstance.h"
#include "CW/Vehicle/CWWheeledVehiclePawn.h"

#include "Data/SNContentsAsset.h"
#include "Data/SNDataAssetManager.h"
#include "Utility/SNUtility.h"

//----------------------------------------------------------------------//
//
//! @brief 武器データのアセットを初期化
//
//! @note 武器のアセットをここでロードしてるけど、後々は必要な時に
//        非同期でロードするように変更したほうが良さそう。
//
//----------------------------------------------------------------------//
void UCWWeaponManager::SetupWeaponDataAsset(){
	// データ管理クラスを取得
	USNDataAssetManager* DataAssetManager(GetCWGameInstance()->GetDataAssetManager());
	// データ管理クラスがない場合はアサート
	CW_ASSERT(DataAssetManager != nullptr, TEXT("Data Asset Manager is null"));
	// 武器のアセットリストを取得
	const USNContentsAsset* WeaponAsset(DataAssetManager->GetContentAsset(FName(TEXT("Weapon"))));
	// データ存在するかチェック
	if(WeaponAsset == nullptr){
		
		CW_LOG(TEXT("Weapon Data is none"));
		
		return;
	}
	// 
	const TMap<FName, TSoftClassPtr<UObject>>& WeaponClassList(WeaponAsset->GetContentClassList());
	
	for(auto& Weapon:WeaponClassList){
		WeaponClassMap.Add(Weapon.Key, Weapon.Value);
	}
}

//----------------------------------------------------------------------//
//
//! @brief 武器のクラス情報を非同期ロード
//
//! @param Key   ロードする武器名
//! @param Class ロード終了時に通知するビークルアクター
//! @param Func  ロード終了時にコールするデリゲート
//
//! @retval 非同期ロードのハンドラ
//
//----------------------------------------------------------------------//
TSharedPtr<FStreamableHandle> UCWWeaponManager::LoadWeaponClass(FName Key, ACWWheeledVehiclePawn* Class, typename TMemFunPtrType<false, ACWWheeledVehiclePawn, void ()>::Type Func){
	// アセットが存在するかチェック
	if(WeaponClassMap.Find(Key) == nullptr){
		return nullptr;
	}
	
	TArray<FSoftObjectPath> ObjectList;
	
	ObjectList.Add(WeaponClassMap[Key].ToSoftObjectPath());
	// 非同期ロード
	return SNUtility::RequestAsyncLoad(ObjectList, Class, Func);
}
