// Fill out your copyright notice in the Description page of Project Settings.


#include "CWMatchingJoinSessionTask.h"

#include "OnlineSessionSettings.h"
#include "Components/TileView.h"
#include "CW/CWDef.h"
#include "CW/System/CWGameInstance.h"
#include "CW/UI/Widget/Matching/CWMatchingJoinSessionMenu.h"
#include "Online/OnlineSessionNames.h"
#include "Online/SNOnlineSystem.h"

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

	USNOnlineSystem* OnlineSystem(GetCWGameInstance()->GetOnlineSystem());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->OnCompleteFindSession.BindDynamic(this, &UCWMatchingJoinSessionTask::OnCompleteSearchSession);

		OnlineSystem->FindSession();
	}
		
	return Result;
}

void UCWMatchingJoinSessionTask::ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	Super::ExitState(Context, Transition);

	USNOnlineSystem* OnlineSystem(GetCWGameInstance()->GetOnlineSystem());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->OnCompleteFindSession.Clear();
	}
}

void UCWMatchingJoinSessionTask::HudPostLoad()
{
	if(UCWMatchingJoinSessionMenu* Menu = Cast<UCWMatchingJoinSessionMenu>(GetHud()))
	{
		Menu->OnJoinButtonClickedDelegate.BindDynamic(this, &UCWMatchingJoinSessionTask::OnStartSearchSession);
	}
}

void UCWMatchingJoinSessionTask::OnStartSearchSession(const FString& Name)
{
	
}


void UCWMatchingJoinSessionTask::OnCompleteSearchSession(bool bResult)
{
	USNOnlineSystem* OnlineSystem(GetCWGameInstance()->GetOnlineSystem());

	const TSharedPtr<FOnlineSessionSearch>& SessionList(OnlineSystem->GetSearchSessionList());

	if(SessionList != nullptr)
	{
		UCWMatchingJoinSessionMenu* Menu = Cast<UCWMatchingJoinSessionMenu>(GetHud());

		if(Menu != nullptr)
		{
			for(auto& Result:SessionList->SearchResults)
			{
				const FOnlineSessionSetting& Setting(Result.Session.SessionSettings.Settings[SEARCH_KEYWORDS]);

				FString RoomName = Setting.Data.ToString();

				Menu->CreateRoomItem(RoomName, Result.Session.NumOpenPrivateConnections);

				
				FString tmp = Result.Session.SessionInfo->ToString();
				FString dbg = Result.Session.SessionInfo->ToDebugString();
				
				FOnlineSessionSetting Name;
				
				//Result.Session.SessionSettings.Get(FName(TEXT("UseSessionName")), Name);
				
				CW_LOG(TEXT("Test."));
			}
		}
	}
}



