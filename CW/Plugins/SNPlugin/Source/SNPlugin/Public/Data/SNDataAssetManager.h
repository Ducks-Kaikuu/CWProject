// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SNDataAssetManager.generated.h"

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
class USNContentsAsset;

/**
 * 
 */
UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class SNPLUGIN_API USNDataAssetManager : public UObject
{
	GENERATED_BODY()

public:
	
private:
	//!< アセットリスト
	UPROPERTY(EditAnyWhere, Category="Data")
	TMap<FName, TObjectPtr<USNContentsAsset>> DataAssetList;
};
