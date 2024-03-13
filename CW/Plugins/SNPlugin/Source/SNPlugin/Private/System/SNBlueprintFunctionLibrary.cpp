// Fill out your copyright notice in the Description page of Project Settings.


#include "System/SNBlueprintFunctionLibrary.h"

#include "SNDef.h"
#include "Kismet/GameplayStatics.h"
#include "Online/SNOnlineSystem.h"
#include "System/SNGameInstance.h"

bool USNBlueprintFunctionLibrary::StartupOnlineSystem()
{
	USNGameInstance* GameInstance(Cast<USNGameInstance>(UGameplayStatics::GetGameInstance(GetPrimaryWorld())));

	if(GameInstance == nullptr)
	{
		SNPLUGIN_LOG(TEXT("Failed to Start Online System because SNGameInstance is nullptr."));

		return false;
	}

	return GameInstance->StartOnlineSystem();
}

void USNBlueprintFunctionLibrary::Login()
{
	USNOnlineSystem* OnlineSystem(GetOnlineSystem());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->Login();	
	}
	
}

void USNBlueprintFunctionLibrary::HostSession()
{
	USNOnlineSystem* OnlineSystem(GetOnlineSystem());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->HostSession();
	}
}

void USNBlueprintFunctionLibrary::FindSession()
{
	USNOnlineSystem* OnlineSystem(GetOnlineSystem());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->FindSession();
	}
}

void USNBlueprintFunctionLibrary::KillSession()
{
	USNOnlineSystem* OnlineSystem(GetOnlineSystem());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->KillSession();
	}
}

USNOnlineSystem* USNBlueprintFunctionLibrary::GetOnlineSystem()
{
	USNGameInstance* GameInstance(Cast<USNGameInstance>(UGameplayStatics::GetGameInstance(GetPrimaryWorld())));

	if(GameInstance == nullptr)
	{
		SNPLUGIN_LOG(TEXT("Failed to get OnlineSyste because SNGameInstance is nullptr."));

		return nullptr;
	}

	if(GameInstance->IsEnabledOnlineSystem() == false)
	{
		SNPLUGIN_LOG(TEXT("Failed to get OnlineSyste because OnlneSystem is nullptr."));

		return nullptr;
	}

	return GameInstance->GetOnlineSystem();
}

