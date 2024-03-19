// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Scene/StateTree/CWMatchingHostSessionTask.h"

#include "CW/System/CWGameInstance.h"
#include "CW/UI/Widget/CWButton.h"
#include "CW/UI/Widget/Matching/CWMatchingHostSessionMenu.h"
#include "Online/SNOnlineSystem.h"
#include "Utility/SNUtility.h"

EStateTreeRunStatus UCWMatchingHostSessionTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	EStateTreeRunStatus Result = Super::Tick(Context, DeltaTime);

	if(bCancel == true)
	{
		FinishTask();

		return EStateTreeRunStatus::Failed;
	}

	if(bExit == true)
	{
		FinishTask();

		return (bSucceed == true) ? EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Failed;
	}
	
	return Result;
}

EStateTreeRunStatus UCWMatchingHostSessionTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	EStateTreeRunStatus Result = Super::EnterState(Context, Transition);

	return Result;
}

void UCWMatchingHostSessionTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);

	USNOnlineSystem* OnlineSystem(GetCWGameInstance()->GetOnlineSystem());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->OnCompleteHostSession.Clear();
	}
}

void UCWMatchingHostSessionTask::HudPostLoad()
{
	UCWMatchingHostSessionMenu* Menu = Cast<UCWMatchingHostSessionMenu>(GetHud());

	if(Menu != nullptr)
	{
		if(UCWButton* Button = Menu->GetCreateButton())
		{
			Button->OnClickedDelegate.AddDynamic(this, &UCWMatchingHostSessionTask::OnCreateButtonClicked);
		}

		if(UCWButton* Button = Menu->GetCancelButton())
		{
			Button->OnClickedDelegate.AddDynamic(this, &UCWMatchingHostSessionTask::OnCancelButtonClicked);
		}
	}	
}


void UCWMatchingHostSessionTask::OnCreateButtonClicked(UCWButton* Button)
{
	USNOnlineSystem* OnlineSystem(GetCWGameInstance()->GetOnlineSystem());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->OnCompleteHostSession.BindDynamic(this, &UCWMatchingHostSessionTask::OnCompleteHostSession);

		FName Name = FName(TEXT("Session"));

		int ConnectionNum = -1;
		
		if(UCWMatchingHostSessionMenu* Menu = Cast<UCWMatchingHostSessionMenu>(GetHud()))
		{
			Name = Menu->GetSessionName();

			ConnectionNum = Menu->GetConnectionNum();
		}

		if(ConnectionNum > 0)
		{
			OnlineSystem->HostSession(ConnectionNum, Name);	
		}
	}
}

void UCWMatchingHostSessionTask::OnCancelButtonClicked(UCWButton* Button)
{
	bCancel = true;
}

void UCWMatchingHostSessionTask::OnCompleteHostSession(FName SessionName, bool bWasSuccessful)
{
	bSucceed = bWasSuccessful;

	bExit = true;
}
