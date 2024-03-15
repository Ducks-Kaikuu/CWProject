// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Scene/StateTree/CWSceneTaskBase.h"
#include "Blueprint/StateTreeTaskBlueprintBase.h"
#include "CWBattleTask.generated.h"

class UCWUserWidgetBase;
/**
 * 
 */
UCLASS()
class CW_API UCWBattleTask : public UCWSceneTaskBase
{
	GENERATED_BODY()

public:

	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;

	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;

};
