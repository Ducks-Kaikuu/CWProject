// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Interfaces/OnlineSessionDelegates.h"
#include "SNOnlineSystem.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FSNCompleteHostSession, FName, InSessionName, bool, bWasSuccessful);
DECLARE_DYNAMIC_DELEGATE_OneParam(FSNCompleteFindSession, bool, bWasSuccessful);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FSNCompleteJoinSession, FName, InSessionName, bool, bResult);

/**
 * 
 */
UCLASS()
class SNPLUGIN_API USNOnlineSystem : public UObject
{
	GENERATED_BODY()

public:
	//! @{@name ログイン処理
	void Login();
	//! @}
	
	//! @{@name ホストとしてセッションを生成
	bool HostSession(int ConnectionNum=4, FName Name=FName(TEXT("Session")));
	//! @}
	
	//! @{@name セッションを検索
	void FindSession();
	//! @}
	
	//! @{@name セッションに参加
	void JoinSession(FOnlineSessionSearchResult SearchResult);
	//! @}
	
	//! @{@name セッションを終了
	void KillSession();
	//! @}

	const TSharedPtr<class FOnlineSessionSearch>& GetSearchSessionList() const ;

	FSNCompleteHostSession OnCompleteHostSession;

	FSNCompleteFindSession OnCompleteFindSession;

	FSNCompleteJoinSession OnCompleteJoinSession;
	
private:
	
	//! @{@name ログインに成功した際のデリゲート
	void OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error);
	//! @}
	
	//! @{@name セッションの作成に成功した際のデリゲート
	void OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful);
	//! @}
	
	//! @{@name セッションの検索が終了した際のデリゲート
	void OnFindSessionsComplete(bool bWasSuccessful);
	//! @}
	
	//! @{@name セッションへの参加が完了した際のでーりゲート
	void OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type Result);
	//! @}

	UPROPERTY(EditAnywhere, Category="Online")
	bool bShouldIdAdvertise = true;
	
	UPROPERTY(EditAnywhere, Category="Online")
	bool bAllowJoinInProgress = true;
	
	UPROPERTY(EditAnywhere, Category="Online")
	bool bAllowInvites = true;
	
	UPROPERTY(EditAnywhere, Category="Online")
	bool bUsesPresence = true;
	
	UPROPERTY(EditAnywhere, Category="Online")
	bool bAllowJoinViaPresense =true;
	
	UPROPERTY(EditAnywhere, Category="Online")
	bool bUseLobbiesIfAvailable = true;
	
	UPROPERTY(EditAnywhere, Category="Online")
	bool bUseLobbiesVoiceChatIfAvailable = true;

	UPROPERTY()
	FName SessionName = NAME_None;
		
	TSharedPtr<class FOnlineSessionSearch> SearchSettings = nullptr;
};

FORCEINLINE const TSharedPtr<FOnlineSessionSearch>& USNOnlineSystem::GetSearchSessionList() const
{
	return SearchSettings;
}
 