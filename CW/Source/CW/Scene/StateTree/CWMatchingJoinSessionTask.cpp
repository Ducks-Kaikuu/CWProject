// Fill out your copyright notice in the Description page of Project Settings.


#include "CWMatchingJoinSessionTask.h"

EStateTreeRunStatus UCWMatchingJoinSessionTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	EStateTreeRunStatus Result = Super::Tick(Context, DeltaTime);

	//FinishTask();
	
	//return EStateTreeRunStatus::Succeeded;
	return Result;
}

EStateTreeRunStatus UCWMatchingJoinSessionTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	EStateTreeRunStatus Result = Super::EnterState(Context, Transition);
	
	return Result;
}

void UCWMatchingJoinSessionTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);
}

