#pragma once

#include "CoreTypes.h"

class USNDataAssetManager;

class ISNDLCModuleInterface:public IModuleInterface
{
public:
	
	virtual TSoftClassPtr<USNDataAssetManager> GetAssetManagerSoftClassPtr() = 0;
};
