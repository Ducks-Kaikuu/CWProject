// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class USNDataAssetManager;

class FCWDLC00Module : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	UPROPERTY(Config, EditAnywhere, Category="DLC00 Custom Setting")
	TObjectPtr<USNDataAssetManager> AssetManager;
};
