// Fill out your copyright notice in the Description page of Project Settings.


#include "CWMatchingJoinSessionTask.h"

#include "CW/CWDef.h"
#include "CW/System/CWGameInstance.h"
#include "CW/UI/Widget/Matching/CWMatchingJoinSessionMenu.h"

#include "OnlineSessionSettings.h"
#include "Online/OnlineSessionNames.h"
#include "Online/SNOnlineSystem.h"

EStateTreeRunStatus UCWMatchingJoinSessionTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	EStateTreeRunStatus Result = Super::Tick(Context, DeltaTime);

	if(bExit == true)
	{
		return (bSucceed == true) ? EStateTreeRunStatus::Succeeded : EStateTreeRunStatus::Failed;
	}
	
	return Result;
}

EStateTreeRunStatus UCWMatchingJoinSessionTask::EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition)
{
	EStateTreeRunStatus Result = Super::EnterState(Context, Transition);

	USNOnlineSystem* OnlineSystem(GetCWGameInstance()->GetOnlineSystem());

	if(OnlineSystem != nullptr)
	{
		OnlineSystem->OnCompleteFindSession.AddDynamic(this, &UCWMatchingJoinSessionTask::OnCompleteSearchSession);

		OnlineSystem->OnCompleteJoinSession.AddDynamic(this, &UCWMatchingJoinSessionTask::OnCompleteJoinSession);
		
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

		OnlineSystem->OnCompleteJoinSession.Clear();
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
	USNOnlineSystem* OnlineSystem(GetCWGameInstance()->GetOnlineSystem());

	if(OnlineSystem != nullptr)
	{
		const TSharedPtr<FOnlineSessionSearch>& SessionList(OnlineSystem->GetSearchSessionList());

		for(auto& Result:SessionList->SearchResults)
		{
			const FOnlineSessionSetting& Setting(Result.Session.SessionSettings.Settings[SEARCH_KEYWORDS]);

			FString RoomName = Setting.Data.ToString();

			if(RoomName == Name)
			{
				OnlineSystem->JoinSession(Result);

				return;
			}
		}
	}
	// ここまで処理が来た場合は接続に失敗
	bSucceed = false;
	// 処理を終了
	bExit = true;
}


void UCWMatchingJoinSessionTask::OnCompleteSearchSession(bool bResult)
{
	USNOnlineSystem* OnlineSystem(GetCWGameInstance()->GetOnlineSystem());

	const TSharedPtr<FOnlineSessionSearch>& SessionList(OnlineSystem->GetSearchSessionList());

	if(SessionList != nullptr)
	{
		// 検索結果が0の場合は終了
		// リトライをいれるべきか...
		if(SessionList->SearchResults.Num() <= 0)
		{
			CW_LOG(TEXT("Host Session is not Found."))
			// 接続失敗判定
			bSucceed = false;
			// 処理を終了
			bExit = true;
			
			return;
		}
		
		UCWMatchingJoinSessionMenu* Menu = Cast<UCWMatchingJoinSessionMenu>(GetHud());

		if(Menu != nullptr)
		{
			for(auto& Result:SessionList->SearchResults)
			{
				const FOnlineSessionSetting& Setting(Result.Session.SessionSettings.Settings[SEARCH_KEYWORDS]);

				FString RoomName = Setting.Data.ToString();

				Menu->ShowRoomItem(RoomName, Result.Session.NumOpenPublicConnections);
			}
		}
	}
}

void UCWMatchingJoinSessionTask::OnCompleteJoinSession(FName SessionName, bool bResult)
{
	bSucceed = bResult;

	bExit = true;

	if(bSucceed == true)
	{
		UCWMatchingSceneBase::SetSessionName(SessionName);
	}
}




