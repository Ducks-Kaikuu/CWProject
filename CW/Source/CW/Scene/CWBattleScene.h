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
	
protected:
	
	void BeginPlay() override;
	
private:
	
	//! @{@name バトルHUDクラス情報の非同期ロードが終了した際のイベント
	void FinishuHudLoad();
	//! @}
	
	//!< バトルHUDのクラス情報
	UPROPERTY(EditAnywhere, Category="HUD")
	TSoftClassPtr<UCWUserWidgetBase> BattleHudClass = nullptr;

	UPROPERTY(EditAnywhere, Category="Bullet")
	TSoftClassPtr<UCWBulletManager> BulletManagerClass = UCWBulletManager::StaticClass();
	
	UPROPERTY(EditAnywhere, Category="Bullet")
	TMap<TSoftClassPtr<ACWBulletBase>, int> SpawnBullet;

	
	
	//!< バトルHUDへのポインタ
	UPROPERTY()
	TObjectPtr<UCWUserWidgetBase> BattleHud = nullptr;

	UPROPERTY()
	TObjectPtr<UCWBulletManager> BulletManager = nullptr;
	
	//!< バトルHUDの非同期ロードのハンドル
	TSharedPtr<FStreamableHandle> HudStreamHandle;
};
