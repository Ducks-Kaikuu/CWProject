// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/UI/Widget/CWUserWidgetBase.h"
#include "CWMatchingJoinSessionMenu.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnJoinButtonClicked, const FString&, SessionName);

class UCWButton;
class UCWRoomItem;
class UListView;
class UTileView;

//----------------------------------------------------------------------//
//
//! @brief 接続用メニュークラス
//
//----------------------------------------------------------------------//
UCLASS()
class CW_API UCWMatchingJoinSessionMenu : public UCWUserWidgetBase
{
	GENERATED_BODY()

public:
	
	//! @{@name 初期化処理
	bool Initialize() override;
	//! @}
	
	//! @{@name ルーム情報を表示
	UCWRoomItem* ShowRoomItem(const FString& SessionName, int ConnectionNum);
	//! @}
	
	//! @{@name 接続ボタンを押された際のデリゲータ
	FOnJoinButtonClicked OnJoinButtonClickedDelegate;
	//! @}
	
private:
	
	//! @{@name 接続ボタンを押された際のデリゲート
	UFUNCTION()
	void OnJoinButtonClicked(UCWButton* Button);
	//! @}
	
	//!< ルーム情報表示用Widgetリスト
	UPROPERTY()
	TArray<TObjectPtr<UCWRoomItem>> RoomItemList;
	
	//!< 表示しているルーム数
	int RoomCount = 0;
};
