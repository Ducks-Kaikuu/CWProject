// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Scene/StateTree/CWMatchingSceneBase.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "CWMatchingTask.generated.h"

class UCWButton;
class UCWMatchingMenu;

UENUM(BlueprintInternalUseOnly)
enum class EMatchingState:uint8
{
	None UMETA(DisplayName = "Not Select"),
	Host UMETA(DisplayName = "Create Host Session"),
	Join UMETA(DisplayName = "Join Session")
};
/**
 * 
 */
UCLASS()
class CW_API UCWMatchingTask : public UCWMatchingSceneBase
{
	GENERATED_BODY()

public:
	
	//! @{@name 毎フレームの更新処理
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;
	//! @}
	
	//! @{@name タスクの開始処理
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	//! @}
	
	//! @{@name タスクの終了処理
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	//! @}

	virtual void HudPostLoad() override;

	UFUNCTION()
	void OnClickHostSession(UCWButton* Button);

	UFUNCTION()
	void OnClickJoinSession(UCWButton* Button);
	
private:
	// 
	UPROPERTY(VisibleAnywhere)
	int MatchingState = (int)EMatchingState::None;

};
