// Fill out your copyright notice in the Description page of Project Settings.
#include "CW/UI/HUD/CWHUD.h"
#include "CW/CWDef.h"
#include "Text/SNDebugTextRenderObject.h"

#include "Engine/Canvas.h"
#include "CanvasItem.h"

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//----------------------------------------------------------------------//
ACWHUD::ACWHUD(){
#if CW_DEBUG
	m_isShowDebugText = true;
	
	DebugDrawObject = NewObject<USNDebugTextRenderObject>();
#else
	m_isShowDebugText = false;
	
	DebugDrawObject = nullptr;
#endif
}

//----------------------------------------------------------------------//
//
//! @brief デストラクタ
//
//----------------------------------------------------------------------//
ACWHUD::~ACWHUD(){
	DebugDrawObject = nullptr;
}

//----------------------------------------------------------------------//
//
//! @brief 更新処理
//
//! @param DeltaTime 経過時間
//
//----------------------------------------------------------------------//
void ACWHUD::Tick(float DeltaTime){
	
	Super::Tick(DeltaTime);
	
#if CW_DEBUG
	
	if(DebugDrawObject != nullptr){
		DebugDrawObject->Tick(DeltaTime);
	}
#endif
}

//----------------------------------------------------------------------//
//
//! @brief 描画した後の処理
//
//----------------------------------------------------------------------//
void ACWHUD::PostRender(){
	
	Super::PostRender();
	
#if CW_DEBUG
	if(DebugDrawObject != nullptr){
		DebugDrawObject->Draw(DebugCanvas);
	}
#endif
}

//----------------------------------------------------------------------//
//
//! @brief デバッグ文字の描画
//
//! @param text           表示するテキスト
//! @param color          カラー
//! @param screenX        スクリーン座標X
//! @param screenY        スクリーン座標Y
//! @param lifeTime       描画時間
//! @param pFont          フォント
//! @param scale          スケール
//! @param bScalePosition スケールをポジションに反映させるか
//
//----------------------------------------------------------------------//
void ACWHUD::DrawString(const FString& text, FLinearColor color, float screenX, float screenY, float lifeTime, UFont* pFont, float scale, bool bScalePosition){
#if CW_DEBUG
	DebugDrawObject->AddString(text, color, screenX, screenY, lifeTime, pFont, scale, bScalePosition);
#endif
}

//----------------------------------------------------------------------//
//
//! @brief デバッグメニューの文字描画
//
//! @param text    表示するテキスト
//! @param screenX スクリーン座標X
//! @param screenY スクリーン座標Y
//! @param color   カラー
//
//----------------------------------------------------------------------//
void ACWHUD::DrawStringForDebugMenu(const FString& text, float screenX, float screenY, FLinearColor color){
#if CW_DEBUG
	
	UFont* pFont = GEngine->GetSmallFont();
	
	FCanvasTextItem textItem(FVector2D(screenX, screenY), FText::FromString(text), pFont, color);
	
	textItem.EnableShadow(FLinearColor::Black);
	
	textItem.Scale = FVector2D(1.0f, 1.0f);
	
	DebugCanvas->DrawItem(textItem);
#endif
}
