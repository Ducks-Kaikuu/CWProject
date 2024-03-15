// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Scene/StateTree/CWBattleTask.h"

EStateTreeRunStatus UCWBattleTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	return Super::Tick(Context, DeltaTime);
}

EStateTreeRunStatus UCWBattleTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	return Super::EnterState(Context, Transition);
}

void UCWBattleTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);
}