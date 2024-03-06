// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "System/SNDLCModuleInterface.h"

class USNDataAssetManager;

class FCWDLC00Module : public ISNDLCModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	TSoftClassPtr<USNDataAssetManager> GetAssetManagerSoftClassPtr() override ;
};
