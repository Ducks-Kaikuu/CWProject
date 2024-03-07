// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "CWWeaponManager.generated.h"

class ACWWheeledVehiclePawn;
/**
 * 
 */
UCLASS()
class CW_API UCWWeaponManager : public UObject
{
	GENERATED_BODY()

public:
	
	//! @{@name 武器データのアセットを初期化
	void SetupWeaponDataAsset();
	//! @}
	
	//! @{@name 武器のクラス情報を非同期ロード
	TSharedPtr<FStreamableHandle> LoadWeaponClass(FName Key, ACWWheeledVehiclePawn* Class=nullptr, typename TMemFunPtrType<false, ACWWheeledVehiclePawn, void ()>::Type Func=nullptr);
	//! @}

	
private:
	
	//!< 武器のクラス情報
	UPROPERTY()
	TMap<FName, TSoftClassPtr<UObject>> WeaponClassMap;
};
