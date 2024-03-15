﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Scene/StateTree/CWSceneTaskBase.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "CWMatchingTask.generated.h"

class UCWMatchingMenu;
/**
 * 
 */
UCLASS()
class CW_API UCWMatchingTask : public UCWSceneTaskBase
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
	
private:

};
