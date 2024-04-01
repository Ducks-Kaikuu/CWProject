// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/SNInputManagerSubsystem.h"
#include "SNDef.h"

#include "EnhancedInputSubsystems.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Utility/SNUtility.h"


void USNInputManagerSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void USNInputManagerSubsystem::AddInputContext(const FName& Name, UInputMappingContext* InputMappingContext)
{
	InputMapContextMap.Add(Name, InputMappingContext);
}

void USNInputManagerSubsystem::SetInputMapping(const FName& Name, bool bClearMapping)
{
	if(InputMapContextMap.Contains(Name) == false)
	{
		SNPLUGIN_LOG(TEXT("InputMappingContext can't Find.[%s]"), *Name.ToString());
		
		return;
	}
	
	APlayerController* PlayerController(SNUtility::GetPlayerController<APlayerController>());

	SNPLUGIN_ASSERT(PlayerController != nullptr, TEXT("PlayerController is nullptr"));

	ULocalPlayer* LocalPlayer(PlayerController->GetLocalPlayer());

	SNPLUGIN_ASSERT(LocalPlayer != nullptr, TEXT("LocalPlayer is nullptr"));

	UEnhancedInputLocalPlayerSubsystem* Subsystem(LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>());

	SNPLUGIN_ASSERT(Subsystem != nullptr, TEXT("Input Subsystem is nullptr."));

	if(bClearMapping == true)
	{
		Subsystem->ClearAllMappings();
	}

	if(UInputMappingContext* IMC = InputMapContextMap[Name])
	{
		if(UEnhancedInputUserSettings* Settings = Subsystem->GetUserSettings()){
			Settings->RegisterInputMappingContext(IMC);
		}
			
		FModifyContextOptions Options = {};
			
		Options.bIgnoreAllPressedKeysUntilRelease = false;
			
		Subsystem->AddMappingContext(IMC, 0, Options);
	}
}


