// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Scene/CWBattleScene.h"

#include "Blueprint/UserWidget.h"
#include "CW/CWDef.h"
#include "CW/UI/Widget/CWMasterWidget.h"
#include "CW/UI/Widget/BattleHUD/CWBattleHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/SNUtility.h"

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//----------------------------------------------------------------------//
ACWBattleScene::ACWBattleScene()
:Super()
{
	
}

//----------------------------------------------------------------------//
//
//! @brief ゲーム開始時に呼ばれる関数
//
//----------------------------------------------------------------------//
void ACWBattleScene::BeginPlay(){
	
	Super::BeginPlay();
	// 弾丸管理クラスが設定されていない場合はアサート
	// (初期値を設定しているので意図的にnullにしないと発生しないはず)
	CW_ASSERT(BulletManagerClass.IsNull() == false, TEXT("The BulletManager class is not configured in Blueprint."));
	// クラス情報をロード
	UClass* Class = Cast<UClass>(BulletManagerClass.LoadSynchronous());
	// ここも失敗しないはず…なのでアサート
	CW_ASSERT(Class != nullptr, TEXT("BulletManager Class is nullptr"));
	// 武器管理クラスを生成
	BulletManager = NewObject<UCWBulletManager>(this, TEXT("BulletManager"));
	// ここも失敗しないはず…なのでアサート
	CW_ASSERT(BulletManager != nullptr, TEXT("Failed to Create BulletManager"));
	
	BulletManager->RegisterComponent();
	
	BulletManager->SetupBulletDataAsset();
	
	if(BattleHudClass.IsNull() == false){
		
		TArray<FSoftObjectPath> ObjectList;
		
		ObjectList.Add(BattleHudClass.ToSoftObjectPath());
		
		HudStreamHandle = SNUtility::RequestAsyncLoad(ObjectList, this, &ACWBattleScene::FinishuHudLoad);
	}
}

//----------------------------------------------------------------------//
//
//! @brief バトルHUDクラス情報の非同期ロードが終了した際のイベント
//
//----------------------------------------------------------------------//
void ACWBattleScene::FinishuHudLoad(){
	
	if((HudStreamHandle == nullptr) || (HudStreamHandle->HasLoadCompleted() == false)){
		return;
	}
	
	UClass* Class(Cast<UClass>(HudStreamHandle->GetLoadedAsset()));
	
	if(Class != nullptr){
		
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		
		BattleHud = CreateWidget<UCWBattleHUD>(PlayerController, Class);
		
		if((GetMasterWidget() != nullptr) && (BattleHud != nullptr)){
			
			GetMasterWidget()->SetLayer(EWidgetLayer::Layer3, BattleHud);
			
			BattleHud->SetVisibility(ESlateVisibility::Visible);
		}
	}
	
	HudStreamHandle = nullptr;
}
