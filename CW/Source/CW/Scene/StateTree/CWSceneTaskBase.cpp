// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Scene/StateTree/CWSceneTaskBase.h"

#include "Chaos/ClusterUnionManager.h"
#include "CW/CWDef.h"
#include "CW/Scene/CWSceneBase.h"
#include "CW/System/CWGameInstance.h"
#include "CW/UI/Widget/CWMasterWidget.h"
#include "CW/UI/Widget/CWUserWidgetBase.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/SNUtility.h"

EStateTreeRunStatus UCWSceneTaskBase::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	EStateTreeRunStatus Result =Super::EnterState(Context, Transition);
	// UIのクラス情報を非同期ロード
	LoadHudClassASync();
	
	return Result; 
}

void UCWSceneTaskBase::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);
	
	if(HudInstance != nullptr){
		
		ACWSceneBase* Scene = Cast<ACWSceneBase>(GetOwnerActor(Context));
		
		if(Scene != nullptr){
			
			UCWMasterWidget* MasterWidget = Scene->GetMasterWidget();
			
			if(MasterWidget != nullptr){
				// レイヤーから削除
				MasterWidget->RemoveLyaer(EWidgetLayer::Layer3, HudInstance);
				// UI情報を破棄
				HudInstance->ConditionalBeginDestroy();
				// nullに設定
				HudInstance = nullptr;
			} else {
				CW_ERROR(TEXT("MasterWidget is nullptr."));
			}
			
		} else {
			CW_ERROR(TEXT("Failed to Get Current Scene."));
		}
	}
}

//----------------------------------------------------------------------//
//
//! @brief UI用のクラス情報を非同期でロード
//
//----------------------------------------------------------------------//
void UCWSceneTaskBase::LoadHudClassASync(){
	
	if((HudClass.IsNull() == false) && (HudInstance == nullptr)){
		
		TArray<FSoftObjectPath> Array;
		
		Array.Add(HudClass.ToSoftObjectPath());
		// 非同期ロード
		HudStreamHandle = SNUtility::RequestAsyncLoad(Array, this, &UCWSceneTaskBase::FinishLoadHudClass); 
	}
}

//----------------------------------------------------------------------//
//
//! @brief 非同期ロードが終了した際のデリゲート
//
//----------------------------------------------------------------------//
void UCWSceneTaskBase::FinishLoadHudClass(){
	
	if(HudStreamHandle->HasLoadCompleted() == false){
		return;
	}
	// クラス情報を取得
	UClass* Class = Cast<UClass>(HudStreamHandle->GetLoadedAsset());
	// nullチェック
	if(Class == nullptr){
		
		CW_ERROR(TEXT("Hud Class is nullptr."));
		
		return;
	}
	
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	
	CW_ASSERT(PlayerController != nullptr, TEXT("PlayerController is nullptr."));
	// Widgetを生成
	HudInstance = Cast<UCWUserWidgetBase>(CreateWidget(PlayerController, Class));
	
	if(HudInstance != nullptr){
		
		ACWSceneBase* Scene = GetCWGameInstance()->GetCurrentScene();
		
		if(Scene != nullptr){
			// マスターを取得
			UCWMasterWidget* MasterWidget = Scene->GetMasterWidget();
			
			if(MasterWidget != nullptr){
				// レイヤーに設定
				MasterWidget->SetLayer(EWidgetLayer::Layer3, HudInstance);
				// 表示を設定
				HudInstance->SetVisibility(ESlateVisibility::Visible);
				// ロード終了を通知
				HudPostLoad();
				
			} else {
				CW_ERROR(TEXT("MasterWidget is nullptr."));
			}
			
		} else {
			CW_ERROR(TEXT("Failed to Get Current Scene."));
		}
	}
}