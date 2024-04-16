// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interfaces/OnlineSessionInterface.h"

#if COMMONUSER_OSSV1
#include "Interfaces/OnlineIdentityInterface.h"
#include "OnlineError.h"
#else
#include "Online/OnlineAsyncOpHandle.h"
#endif

#include "SNOnlineSystem.generated.h"

class IOnlineSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSNCompleteHostSession, FName, InSessionName, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSNCompleteFindSession, bool, bWasSuccessful);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSNCompleteJoinSession, FName, InSessionName, bool, bResult);

/**
 * 
 */
UCLASS(Blueprintable)
class SNPLUGIN_API USNOnlineSystem : public UObject
{
	GENERATED_BODY()

public:

	void Initialize();
	
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
	void KillSession(const FName& SessionName);
	//! @}

	const TSharedPtr<class FOnlineSessionSearch>& GetSearchSessionList() const ;

	UPROPERTY(BlueprintAssignable, Category = "Online|Session")
	FSNCompleteHostSession OnCompleteHostSession;

	UPROPERTY(BlueprintAssignable, Category = "Online|Session")
	FSNCompleteFindSession OnCompleteFindSession;

	UPROPERTY(BlueprintAssignable, Category = "Online|Session")
	FSNCompleteJoinSession OnCompleteJoinSession;



	FString GetNickname() const ;
	
protected:
	// Lylaからのテスト
	struct FOnlineContextCache
	{
#if COMMONUSER_OSSV1
		/** Pointer to base subsystem, will stay valid as long as game instance does */
		IOnlineSubsystem* OnlineSubsystem = nullptr;

		/** Cached identity system, this will always be valid */
		IOnlineIdentityPtr IdentityInterface;

		/** Last connection status that was passed into the HandleNetworkConnectionStatusChanged hander */
		EOnlineServerConnectionStatus::Type	CurrentConnectionStatus = EOnlineServerConnectionStatus::Normal;
#else
		/** Online services, accessor to specific services */
		UE::Online::IOnlineServicesPtr OnlineServices;
		/** Cached auth service */
		UE::Online::IAuthPtr AuthService;
		/** Login status changed event handle */
		UE::Online::FOnlineEventDelegateHandle LoginStatusChangedHandle;
		/** Connection status changed event handle */
		UE::Online::FOnlineEventDelegateHandle ConnectionStatusChangedHandle;
		/** Last connection status that was passed into the HandleNetworkConnectionStatusChanged hander */
		UE::Online::EOnlineServicesConnectionStatus CurrentConnectionStatus = UE::Online::EOnlineServicesConnectionStatus::NotConnected;
#endif

		/** Resets state, important to clear all shared ptrs */
		void Reset()
		{
#if COMMONUSER_OSSV1
			OnlineSubsystem = nullptr;
			IdentityInterface.Reset();
			CurrentConnectionStatus = EOnlineServerConnectionStatus::Normal;
#else
			OnlineServices.Reset();
			AuthService.Reset();
			CurrentConnectionStatus = UE::Online::EOnlineServicesConnectionStatus::NotConnected;
#endif
		}
	};

	virtual void CreateOnlineContexts();
	
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

	FOnlineContextCache* DefaultContextInternal = nullptr;

	FOnlineContextCache* PlatformContextInternal = nullptr;
	
	TSharedPtr<class FOnlineSessionSearch> SearchSettings = nullptr;
};

FORCEINLINE const TSharedPtr<FOnlineSessionSearch>& USNOnlineSystem::GetSearchSessionList() const
{
	return SearchSettings;
}
 