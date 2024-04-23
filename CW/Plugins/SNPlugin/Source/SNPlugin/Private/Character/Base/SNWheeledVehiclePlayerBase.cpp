// Fill out your copyright notice in the Description page of Project Settings.

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

void ASNWheeledVehiclePlayerBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for(auto& Action:InputActionMap)
	{
		Action.Value->ConditionalBeginDestroy();
	}

	InputActionMap.Reset();
}


void ASNWheeledVehiclePlayerBase::AddInputAction(const FName& Name, USNActionBase* Action)
{
	InputActionMap.Add(Name, Action);
}

USNActionBase* ASNWheeledVehiclePlayerBase::GetAction(const FName& Name)
{
	USNActionBase* Action = nullptr;
	
	if(InputActionMap.Contains(Name) == true)
	{
		Action = InputActionMap[Name];
	}

	return Action;
}

void ASNWheeledVehiclePlayerBase::ExecuteInputAction_OnServer_Implementation(const FName& Name, const FInputActionValue& InputActionValue)
{
	ISNPlayablePawnInterface::ExecuteAction(Name, InputActionValue);
	
	SNPLUGIN_LOG(TEXT("Server Input Action is calling."));
}

void ASNWheeledVehiclePlayerBase::ExecuteActionOnServer(const FName& Name, const FInputActionValue& InputActionValue)
{
	ExecuteInputAction_OnServer(Name, InputActionValue);
}



