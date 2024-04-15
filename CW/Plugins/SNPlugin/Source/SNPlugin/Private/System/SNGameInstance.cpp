// Fill out your copyright notice in the Description page of Project Settings.
#include "System/SNGameInstance.h"
#include "SNDef.h"
#include "..\..\Public\Online\SNOnlineSystem.h"
#include "GameplayTags/SNGameplayTags.h"
#include "Data/SNDataAssetManager.h"

#include "Components/GameFrameworkComponentManager.h"

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//----------------------------------------------------------------------//
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
	// クラス情報をロード
	UClass* AssetClass = DataAssetManagerClass.LoadSynchronous();
	// nullチェック
	if(AssetClass != nullptr)
	{
		// インスタンスを生成
		DataAssetManager = NewObject<USNDataAssetManager>(this, AssetClass);
	}
	
	SNPLUGIN_ASSERT(DataAssetManager != nullptr, TEXT("DataAssetManager Is Null"));
	
	DataAssetManager->SetupDLCContents();
	// クラス情報が設定されているかチェック
	if(OnlineSystemClass.IsNull() == false)
	{
		UClass* OnlineClass = OnlineSystemClass.LoadSynchronous();
		
		if(OnlineClass != nullptr)
		{
			OnlineSystem = NewObject<USNOnlineSystem>(this, OnlineClass);
			
			if(OnlineSystem != nullptr)
			{
				SNPLUGIN_LOG(TEXT("Online System is Enabled."));
			}
		}
	}
}
