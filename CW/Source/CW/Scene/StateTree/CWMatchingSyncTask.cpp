// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Scene/StateTree/CWMatchingSyncTask.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "SNDef.h"
#include "CW/CWDef.h"
#include "CW/UI/Widget/Matching/CWMatchingSyncMenu.h"
#include "Interfaces/OnlineSessionInterface.h"


EStateTreeRunStatus UCWMatchingSyncTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	EStateTreeRunStatus Result = Super::Tick(Context, DeltaTime);

	IOnlineSubsystem* const OnlineSubsystem = Online::GetSubsystem(GetWorld());
	
	SNPLUGIN_ASSERT(OnlineSubsystem != nullptr, TEXT("OnlineSubsystem is nullptr"));
	
	IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
	
	if(Sessions.IsValid())
	{
		EOnlineSessionState::Type Type = Sessions->GetSessionState(UCWMatchingSceneBase::GetSessionName());

		CW_LOG(TEXT("Update."));
	}
	
	return Result;
}

EStateTreeRunStatus UCWMatchingSyncTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	EStateTreeRunStatus Result = Super::EnterState(Context, Transition);

	return Result;
}

void UCWMatchingSyncTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);

}

void UCWMatchingSyncTask::HudPostLoad()
{
	UCWMatchingSyncMenu* Menu = Cast<UCWMatchingSyncMenu>(GetHud());

	if(Menu != nullptr)
	{
		Menu->SetSessionName(UCWMatchingSceneBase::GetSessionName());
	}
}

