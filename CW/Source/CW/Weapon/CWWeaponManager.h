// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CWWeaponManager.generated.h"

/**
 * 
 */
UCLASS()
class CW_API UCWWeaponManager : public UObject
{
	GENERATED_BODY()

public:
	
	void SetupWeaponDataAsset();
	
private:
	UPROPERTY()
	TMap<FName, TObjectPtr<UClass>> WeaponClassMap;
};
