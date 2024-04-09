// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Scene/StateTree/CWMatchingTask.h"

#include "CW/CWDef.h"
#include "CW/Scene/CWSceneDirector.h"
#include "CW/UI/Widget/Matching/CWMatchingMenu.h"
#include "Input/SNInputManagerSubsystem.h"

EStateTreeRunStatus UCWMatchingTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	EStateTreeRunStatus Result = Super::Tick(Context, DeltaTime);

	if(MatchingState != (int)EMatchingState::None)
	{
		FinishTask();

		return EStateTreeRunStatus::Succeeded; 
	}
	
	return Result;
}

EStateTreeRunStatus UCWMatchingTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	EStateTreeRunStatus Result = Super::EnterState(Context, Transition);

	USNInputManagerSubsystem* InputManagerSubsystem(GetCwInputManagerSubsystem());

	if(InputManagerSubsystem != nullptr)
	{
		InputManagerSubsystem->EnableInputMapping(FName(TEXT("Menu")));
	}
	return Result;
}

void UCWMatchingTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);
}

void UCWMatchingTask::HudPostLoad()
{
	Super::HudPostLoad();

	UCWMatchingMenu* Menu = Cast<UCWMatchingMenu>(GetHud());

	if(Menu != nullptr)
	{
		if(UCWButton* Button = Menu->GetHostSessionButton())
		{
			Button->OnClickedDelegate.AddDynamic(this, &UCWMatchingTask::OnClickHostSession);
		}

		if(UCWButton* Button = Menu->GetJoinSessionButton())
		{
			Button->OnClickedDelegate.AddDynamic(this, &UCWMatchingTask::OnClickJoinSession);
		}
	}
}

void UCWMatchingTask::OnClickHostSession(UCWButton* Button)
{
	MatchingState = (int)EMatchingState::Host;
}

void UCWMatchingTask::OnClickJoinSession(UCWButton* Button)
{
	MatchingState = (int)EMatchingState::Join;
}

