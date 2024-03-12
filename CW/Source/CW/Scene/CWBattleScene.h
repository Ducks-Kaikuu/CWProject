// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Bullet/CWBulletManager.h"
#include "CW/Scene/CWSceneBase.h"
#include "CWBattleScene.generated.h"

class UCWBulletManager;
class ACWBulletBase;
struct FStreamableHandle;
class UCWUserWidgetBase;
/**
 * 
 */
UCLASS()
class CW_API ACWBattleScene : public ACWSceneBase
{
	GENERATED_BODY()

public:
	
	//! @{@name デフォルトコンストラクタ
	ACWBattleScene();
	//! @}

	UCWBulletManager* GetBulletManager();
	
protected:
	
	void BeginPlay() override;
	
private:
	
	//! @{@name バトルHUDクラス情報の非同期ロードが終了した際のイベント
	void FinishuHudLoad();
	//! @}
	
	//!< バトルHUDのクラス情報
	UPROPERTY(EditAnywhere, Category="HUD")
	TSoftClassPtr<UCWUserWidgetBase> BattleHudClass = nullptr;
	
	//!< 弾丸管理クラス情報
	UPROPERTY(EditAnywhere, Category="Bullet")
	TSoftClassPtr<UCWBulletManager> BulletManagerClass = UCWBulletManager::StaticClass();
	
	//!< バトルHUDへのポインタ
	UPROPERTY()
	TObjectPtr<UCWUserWidgetBase> BattleHud = nullptr;
	
	//!< 弾丸管理クラス
	UPROPERTY()
	TObjectPtr<UCWBulletManager> BulletManager = nullptr;
	
	//!< バトルHUDの非同期ロードのハンドル
	TSharedPtr<FStreamableHandle> HudStreamHandle;
};

FORCEINLINE UCWBulletManager* ACWBattleScene::GetBulletManager()
{
	return BulletManager;
}