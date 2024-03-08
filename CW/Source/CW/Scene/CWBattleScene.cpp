// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Scene/CWBattleScene.h"

#include "Blueprint/UserWidget.h"
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

void ACWBattleScene::BeginPlay(){
	
	Super::BeginPlay();
	
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
