// Fill out your copyright notice in the Description page of Project Settings.
#include "Action/SNActionBase.h"
#include "EnhancedInputComponent.h"

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//----------------------------------------------------------------------//
USNActionBase::USNActionBase()
:Super()
,Owner(nullptr)
{
	
}

//----------------------------------------------------------------------//
//
//! @brief デストラクタ
//
//----------------------------------------------------------------------//
USNActionBase::~USNActionBase(){
	Owner = nullptr;
}

void USNActionBase::Initialize(UEnhancedInputComponent* InputComponent, const UInputAction* InputAction, AActor* Object){
	
	Owner = Object;
	
	InputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &USNActionBase::InputAction);
}

//----------------------------------------------------------------------//
//
//! @brief 入力からのアクション
//
//! @param InputActionValue 入力情報
//
//----------------------------------------------------------------------//
void	USNActionBase::InputAction(const FInputActionValue& InputActionValue){
	// 実行処理
	ExecAction(InputActionValue);
}
