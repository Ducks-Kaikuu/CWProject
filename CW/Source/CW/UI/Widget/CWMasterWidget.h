// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/UI/Widget/CWUserWidgetBase.h"
#include "CW/UI/CWUIDef.h"
#include "CWMasterWidget.generated.h"

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
class UCanvasPanel;

/**
 * 
 */
UCLASS()
class CW_API UCWMasterWidget : public UCWUserWidgetBase
{
	GENERATED_BODY()

public:
	
	//! @{@name デフォルトコンストラクタ
	UCWMasterWidget();
	//! @}
	
	//! @{@name 初期化処理
	void Init();
	//! @}
	
	//! @{@name レイヤーにウィジェットを設定
	void SetLayer(EWidgetLayer Layer, UCWUserWidgetBase* Widget);
	//! @}
	
private:
	//!< レイヤー用パネル
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UCanvasPanel> LayerPanel[(int)EWidgetLayer::Num];
};
