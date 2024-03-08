// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/UI/Widget/CWMasterWidget.h"

#include "Landscape.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "CW/CWDef.h"

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//----------------------------------------------------------------------//
UCWMasterWidget::UCWMasterWidget()
:Super()
{
	for(int i=0 ; i<(int)EWidgetLayer::Num ; ++i){
		LayerPanel[i]=nullptr;
	}
}

//----------------------------------------------------------------------//
//
//! @brief 初期化処理
//
//----------------------------------------------------------------------//
void UCWMasterWidget::Init(){
	
	for(int i=0 ; i<(int)EWidgetLayer::Num ; ++i){
		// レイヤー名を生成
		FName Name(*FString::Printf(TEXT("Layer%d"), i));
		// レイヤー用パネルを取得
		LayerPanel[i] = Cast<UCanvasPanel>(GetWidgetFromName(Name));
	}
}

//----------------------------------------------------------------------//
//
//! @brief レイヤーにウィジェットを設定
//
//! @param Layer  レイヤー番号
//! @param Widget 登録するウィジェット
//
//----------------------------------------------------------------------//
void UCWMasterWidget::SetLayer(EWidgetLayer Layer, UCWUserWidgetBase* Widget){
	// レンジチェック
	CW_ASSERT(Layer < EWidgetLayer::Num, TEXT("Widget Layer is Invalid"));
	// nullチェック
	if(Widget == nullptr){
		
		CW_WARNING(TEXT("SetLayer : Widget is nullptr\n"));
		
		return;
	}
	// nullチェック
	if(LayerPanel[(int)Layer] == nullptr){
		
		CW_WARNING(TEXT("SetLayer : Layer Panel is nullptr -> %d"), (int)Layer);
		
		return;
	}
	// キャンバスを取得
	UCanvasPanelSlot* CanvasPanelSlot(Cast<UCanvasPanelSlot>(LayerPanel[(int)Layer]->AddChildToCanvas(Widget)));
	// nullチェック
	if(CanvasPanelSlot != nullptr){
		// アンカーを設定
		CanvasPanelSlot->SetAnchors(FAnchors(0, 0, 1, 1));
		// オフセットを設定
		CanvasPanelSlot->SetOffsets(FMargin(0, 0, 0, 0));
	}
}
