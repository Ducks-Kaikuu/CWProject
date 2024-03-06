#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "CWDLC00Setting.generated.h"

class USNDataAssetManager;

UCLASS(Config=CWDLC00, ConfigDoNotCheckDefaults)
class CWDLC00_API UCWDLC00Setting : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	
	//! @{@name デフォルトコンストラクタ
	UCWDLC00Setting();
	//! @}
	
	UPROPERTY(EditAnywhere, config, Category="DLC00 Contents Asset")
	TSoftClassPtr<USNDataAssetManager> ContentsAssetManager = nullptr;
};