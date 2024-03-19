// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "CWSceneTaskBase.generated.h"

struct FStreamableHandle;
class UCWUserWidgetBase;
/**
 * 
 */
UCLASS()
class CW_API UCWSceneTaskBase : public UStateTreeTaskBlueprintBase
{
	GENERATED_BODY()

public:
	
	//! @{@name タスク開始
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	//! @}
	
	//! @{@name タスク終了
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	//! @}

	virtual void HudPostLoad(){};

	UCWUserWidgetBase* GetHud();
	
private:
	
	//! @{@name UI用のクラス情報を非同期でロード
	void LoadHudClassASync();
	//! @}
	
	//! @{@name 非同期ロードが終了した際のデリゲート
	void FinishLoadHudClass();
	//! @}
	
	//!< UI用のクラス情報
	UPROPERTY(EditAnywhere, Category="Scene|UI")
	TSoftClassPtr<UCWUserWidgetBase> HudClass = nullptr;
	
	//!< UI用クラスのインスタンス
	UPROPERTY()
	TObjectPtr<UCWUserWidgetBase> HudInstance = nullptr;
	
	//!< Widgetの非同期ロードのハンドル
	TSharedPtr<FStreamableHandle> HudStreamHandle;
};

FORCEINLINE UCWUserWidgetBase* UCWSceneTaskBase::GetHud()
{
	return HudInstance;
}