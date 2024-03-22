// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/UI/Widget/CWUserWidgetBase.h"
#include "CWRoomItem.generated.h"

class UTextBlock;
class UCWButton;

//----------------------------------------------------------------------//
//
//! @brief ルーム情報管理用Widget
//
//----------------------------------------------------------------------//
UCLASS()
class CW_API UCWRoomItem : public UCWUserWidgetBase
{
	GENERATED_BODY()

public:
	
	//! @{@name 初期化処理
	bool Initialize() override;
	//! @}
	
	//! @{@name ルーム情報を設定
	void SetRoom(const FString& Name, int Num);
	//! @}
	
	//! @{@name 接続用のボタンを取得
	UCWButton* GetJoinButton();
	//! @}
	
	//! @{@name セッション名を取得
	FString GetSessionName() const ;
	//! @}
	
private:
	
	//!< 接続用のボタン
	UPROPERTY()
	TObjectPtr<UCWButton> JoinButton = nullptr;
	
	//!< セッション名
	UPROPERTY()
	TObjectPtr<UTextBlock> SessionName = nullptr;
	
	//!< 接続数
	UPROPERTY()
	TObjectPtr<UTextBlock> ConnectionNum = nullptr;
};

//----------------------------------------------------------------------//
//
//! @brief 接続用のボタンを取得
//
//! @retval ボタンへのポインタ
//
//----------------------------------------------------------------------//
FORCEINLINE UCWButton* UCWRoomItem::GetJoinButton(){
	return JoinButton;
}

