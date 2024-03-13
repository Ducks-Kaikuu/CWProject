// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "SNOnlineSystem.generated.h"

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
	bool HostSession();
	//! @}
	
	//! @{@name セッションを検索
	void FindSession();
	//! @}
	
	//! @{@name セッションを終了
	void KillSession();
	//! @}
	
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
	
	//! @{@name セッションに参加
	void JoinSession(FOnlineSessionSearchResult SearchResult);
	//! @}
	
	//! @{@name セッションへの参加が完了した際のでーりゲート
	void OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type Result);
	//! @}
	
	//!< セッション名
	UPROPERTY(EditAnywhere, Category="Online")
	FName SessionName = FName(TEXT("Session"));
	
	//!< セッションへの接続数
	UPROPERTY(EditAnywhere, Category="Online")
	int ConnectionNum = 4;
	
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
	
	TSharedPtr<class FOnlineSessionSearch> SearchSettings = nullptr;
};
