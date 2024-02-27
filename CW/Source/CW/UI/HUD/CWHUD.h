// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/HUD/SNHUDBase.h"
#include "CWHUD.generated.h"

class USNDebugTextRenderObject;

//----------------------------------------------------------------------//
//
//! @brief HUDクラス
//
//----------------------------------------------------------------------//
UCLASS()
class CW_API ACWHUD : public ASNHUDBase
{
	GENERATED_BODY()
	
public:
	
	//! @{@name デフォルトコンストラクタ
	ACWHUD();
	//! @}
	
	//! @{@name デストラクタ
	~ACWHUD();
	//! @}
	
	//! @{@name 更新処理
	virtual void Tick(float DeltaTime) override ;
	//! @}
	
	//! @{@name 描画処理
	virtual void PostRender() override ;
	//! @}
	
	//! @{@name デバッグ文字の描画
	void DrawString(const FString& text, FLinearColor color, float screenX, float screenY, float lifeTime = 0.0f, UFont* pFont = NULL, float scale = 1.0f, bool bScalePosition = false);
	//! @}
	
	//! @{@name デバッグメニューの文字描画
	void DrawStringForDebugMenu(const FString& text, float screenX, float screenY, FLinearColor color);
	//! @}
	
private:
	//!< @brief デバッグ描画用オブジェクト
	TObjectPtr<USNDebugTextRenderObject> DebugDrawObject;
	
	// 
	bool				m_isShowDebugText;
};
