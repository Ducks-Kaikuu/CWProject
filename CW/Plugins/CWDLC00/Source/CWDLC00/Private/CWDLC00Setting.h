#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "CWDLC00Setting.generated.h"

class USNDataAssetManager;

UCLASS(Config=CWDLC00, ConfigDoNotCheckDefaults)
class CWDLC00_API UCWDLC00Setting : public UDeveloperSettings
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditAnywhere, Category="DLC00 Contents Asset")
	TObjectPtr<USNDataAssetManager> ContentsAssetManager = nullptr;
};