// Fill out your copyright notice in the Description page of Project Settings.
#include "System/SNGameInstance.h"
#include "SNDef.h"
#include "..\..\Public\Online\SNOnlineSystem.h"
#include "GameplayTags/SNGameplayTags.h"
#include "Data/SNDataAssetManager.h"

#include "Components/GameFrameworkComponentManager.h"

USNGameInstance::USNGameInstance()
:Super()
,DataAssetManagerClass(USNDataAssetManager::StaticClass())
{
	
}

//----------------------------------------------------------------------//
//
//! @brief 初期化処理
//
//----------------------------------------------------------------------//
void USNGameInstance::Init()
{
	Super::Init();
	
	UGameFrameworkComponentManager* ComponentManager = GetSubsystem<UGameFrameworkComponentManager>(this);
	
	if(ensure(ComponentManager)){
		ComponentManager->RegisterInitState(SNGameplayTags::InitState_Spawned        , false, FGameplayTag());
		ComponentManager->RegisterInitState(SNGameplayTags::InitState_DataAvailable  , false, SNGameplayTags::InitState_Spawned);
		ComponentManager->RegisterInitState(SNGameplayTags::InitState_DataInitialized, false, SNGameplayTags::InitState_DataAvailable);
	}

	if(DataAssetManagerClass.IsNull() == false){

		UClass* Class = DataAssetManagerClass.LoadSynchronous();
		
		if(Class != nullptr)
		{
			DataAssetManager = NewObject<USNDataAssetManager>(this, Class);
		}
	}

	SNPLUGIN_ASSERT(DataAssetManager != nullptr, TEXT("DataAssetManager Is Null"));

	DataAssetManager->SetupDLCContents();
}

bool USNGameInstance::StartOnlineSystem()
{
	UWorld* World(GetWorld());

	SNPLUGIN_ASSERT(World != nullptr, TEXT("World is nullptr."));
	
	OnlineSystem = NewObject<USNOnlineSystem>(World);

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->Login();
	}
	return (OnlineSystem != nullptr) ? true : false;
}

