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
	
	void SetupWeaponDataAsset();

	TSharedPtr<FStreamableHandle> LoadWeaponClass(FName Key, ACWWheeledVehiclePawn* Class=nullptr, typename TMemFunPtrType<false, ACWWheeledVehiclePawn, void ()>::Type Func=nullptr);
	
private:

	UPROPERTY()
	TMap<FName, TSoftClassPtr<UObject>> WeaponClassMap;
};
