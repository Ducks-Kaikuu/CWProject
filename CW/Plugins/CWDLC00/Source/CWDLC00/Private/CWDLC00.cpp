// Copyright Epic Games, Inc. All Rights Reserved.

#include "CWDLC00.h"

#include "CWDLC00Setting.h"
#include "CW/System/CWGameInstance.h"
#include "Data/SNDataAssetManager.h"
#include "Utility/SNUtility.h"

#define LOCTEXT_NAMESPACE "FCWDLC00Module"

void FCWDLC00Module::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

TSoftClassPtr<USNDataAssetManager> FCWDLC00Module::GetAssetManagerSoftClassPtr()
{
	const UCWDLC00Setting* AssetSetting = GetDefault<UCWDLC00Setting>();

	TSoftClassPtr<USNDataAssetManager> SoftClassPtr;
	
	if(AssetSetting != nullptr)
	{
		SoftClassPtr = AssetSetting->ContentsAssetManager;
	}

	return SoftClassPtr;		
}

void FCWDLC00Module::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCWDLC00Module, CWDLC00)