// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "CWButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCWButtonClicked, UCWButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCWButtonHovered, UCWButton*, Button);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCWButtonUnhovered, UCWButton*, Button);

/**
 * 
 */
UCLASS()
class CW_API UCWButton : public UButton
{
	GENERATED_BODY()
	
public:
	
	//! @{@name デフォルトコンストラクタ
	UCWButton(const FObjectInitializer& ObjectInitializer);
	//! @}
	
	//! @{@name ボタンクリック時のイベント
	FCWButtonClicked OnClickedDelegate;
	//! @}
	
	//! @{@name ボタンにホバー時のイベント
	FCWButtonHovered OnHoveredDelegate;
	//! @}
	
	//! @{@name ボタンにホバーアウト時のイベント
	FCWButtonUnhovered OnUnhoveredDelegate;
	//! @}
	
	void BeginDestroy() override;
	
protected:
	
	//! @{@name ボタンが押された時に呼ばれる
	UFUNCTION()
	void OnButtonClicked();	
	//! @}
	
	//! @{@name ボタンにホバー時のイベント
	UFUNCTION()
	void OnButtonHovered();
	//! @}
	
	//! @{@name ボタンにホバーアウト時のイベント
	UFUNCTION()
	void OnButtonUnhovered();
	//! @}
};
