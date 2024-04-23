﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/Base/SNWheeledVehiclePlayerBase.h"
#include "SNDef.h"
#include "Action/SNActionBase.h"
#include "Utility/SNUtility.h"
#include "Character/SNPlayerController.h"

//----------------------------------------------------------------------//
//
//! @brief プレイヤーインプットコンポーネントの初期化
//
//! @param PlayerInputComponent インプットコンポーネント
//
//----------------------------------------------------------------------//
void ASNWheeledVehiclePlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// プレイヤーコントローラ
	ASNPlayerController* PlayerController(SNUtility::GetPlayerController<ASNPlayerController>());
	// nullチェック
	if(PlayerController != nullptr){
		// 入力の初期化処理
		PlayerController->InitializeInput();
		
		SNPLUGIN_LOG(TEXT("Setup Player Input Component."));
	}
}

//----------------------------------------------------------------------//
//
//! @brief 終了処理
//
//! @param EndPlayReason 終了の理由
//
//----------------------------------------------------------------------//
void ASNWheeledVehiclePlayerBase::EndPlay(const EEndPlayReason::Type EndPlayReason){
	
	Super::EndPlay(EndPlayReason);
	
	for(auto& Action:InputActionMap){
		// アクションを破棄
		Action.Value->ConditionalBeginDestroy();
	}
	// アクションリストをリセット
	InputActionMap.Reset();
}


//----------------------------------------------------------------------//
//
//! @brief 入力された際に呼ばれるアクションを追加
//
//! @param Name   アクション名
//! @param Action アクションへのポインタ
//
//----------------------------------------------------------------------//
void ASNWheeledVehiclePlayerBase::AddInputAction(const FName& Name, USNActionBase* Action){
	InputActionMap.Add(Name, Action);
}

//----------------------------------------------------------------------//
//
//! @brief アクションを取得
//
//! @param Name アクション名
//
//! @retval アクションへのポインタ
//
//----------------------------------------------------------------------//
USNActionBase* ASNWheeledVehiclePlayerBase::GetAction(const FName& Name){
	
	USNActionBase* Action = nullptr;
	
	if(InputActionMap.Contains(Name) == true){
		Action = InputActionMap[Name];
	}
	
	return Action;
}

//----------------------------------------------------------------------//
//
//! @brief サーバー側でアクションを実行
//
//! @param Name             アクション名
//! @param InputActionValue 入力値
//
//----------------------------------------------------------------------//
void ASNWheeledVehiclePlayerBase::ExecuteActionOnServer(const FName& Name, const FInputActionValue& InputActionValue){
	ExecuteInputAction_OnServer(Name, InputActionValue);
}

//----------------------------------------------------------------------//
//
//! @brief 入力からアクション実行用のレプリケーション
//
//! @param Name             アクション名
//! @param InputActionValue 入力値
//
//----------------------------------------------------------------------//
void ASNWheeledVehiclePlayerBase::ExecuteInputAction_OnServer_Implementation(const FName& Name, const FInputActionValue& InputActionValue){
	
	ISNPlayablePawnInterface::ExecuteAction(Name, InputActionValue);
	
	SNPLUGIN_LOG(TEXT("Server Input Action is calling. %f : %f"), InputActionValue[0], InputActionValue[1]);
}
