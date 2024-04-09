// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Scene/StateTree/CWBattleTask.h"
#include "CW/CWDef.h"

#include "Input/SNInputManagerSubsystem.h"

EStateTreeRunStatus UCWBattleTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	return Super::Tick(Context, DeltaTime);
}

EStateTreeRunStatus UCWBattleTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	USNInputManagerSubsystem* InputManagerSubsystem(GetCwInputManagerSubsystem());

	if(InputManagerSubsystem != nullptr)
	{
		InputManagerSubsystem->EnableInputMapping(FName(TEXT("Battle")));
	}
	
	return Super::EnterState(Context, Transition);
}

void UCWBattleTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);
}