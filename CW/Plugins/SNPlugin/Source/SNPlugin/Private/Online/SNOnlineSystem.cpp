﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Online\SNOnlineSystem.h"
#include "SNDef.h"

#include "GameFramework/PlayerState.h"
#include "Kismet/GameplayStatics.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "Online/OnlineSessionNames.h"
#include "OnlineSessionClient.h"
#include "OnlineSessionSettings.h"

//----------------------------------------------------------------------//
//
//! @brief ログイン処理
//
//----------------------------------------------------------------------//
void USNOnlineSystem::Login(){
	
	IOnlineSubsystem* OnlineSubsystem(Online::GetSubsystem(GetWorld()));
	
	SNPLUGIN_ASSERT(OnlineSubsystem != nullptr, TEXT("OnlineSubsystem is nullptr"));
	
	IOnlineIdentityPtr Identity(OnlineSubsystem->GetIdentityInterface());
	// OnlineIdentityが有効なものかチェック
	if(Identity.IsValid()){
		// プレイヤーコントローラを取得
		APlayerController* PlayerController(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		
		SNPLUGIN_ASSERT(PlayerController != nullptr, TEXT("PlayerController is nullptr"));
		// ローカルプレイヤーを取得
		ULocalPlayer* LocalPlayer(PlayerController->GetLocalPlayer());
		
		if(LocalPlayer != nullptr){
			// コントローラIDを取得
			int Id = LocalPlayer->GetControllerId();
			
			if(Identity->GetLoginStatus(Id) != ELoginStatus::LoggedIn){
				
				SNPLUGIN_WARNING(TEXT("CommandLine : %s"), FCommandLine::Get());
				
				Identity->AddOnLoginCompleteDelegate_Handle(Id, FOnLoginCompleteDelegate::CreateUObject(this, &USNOnlineSystem::OnLoginComplete));
				
				Identity->AutoLogin(Id);
			}
			
			ELoginStatus::Type Status = Identity->GetLoginStatus(Id);
			
			SNPLUGIN_LOG(TEXT("Login Status : %s"), ELoginStatus::ToString(Status));
		}
	}
}

//----------------------------------------------------------------------//
//
//! @brief ホストとしてセッションを生成
//
//! @retval true  正常終了
//! @retval false 異常終了
//
//----------------------------------------------------------------------//
bool USNOnlineSystem::HostSession(int ConnectionNum, FName Name){
	
	IOnlineSubsystem* const OnlineSubsystem = Online::GetSubsystem(GetWorld());
	
	SNPLUGIN_ASSERT(OnlineSubsystem != nullptr, TEXT("OnlineSubsystem is nullptr"));

	SessionName = Name;
	
	IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
	
	if(Sessions.IsValid()){
		
		TSharedPtr<class FOnlineSessionSettings> SessionSettings(MakeShareable(new FOnlineSessionSettings()));
		
		SNPLUGIN_ASSERT(SessionSettings != nullptr, TEXT("Failed to allocate Session Settings."));
		// 生成するセッションの設定
		SessionSettings->NumPublicConnections			= ConnectionNum;
		SessionSettings->NumPrivateConnections			= 0;
		SessionSettings->bShouldAdvertise				= bShouldIdAdvertise;
		SessionSettings->bAllowJoinInProgress			= bAllowJoinInProgress;
		SessionSettings->bAllowInvites					= bAllowInvites;
		SessionSettings->bUsesPresence					= bUsesPresence;
		SessionSettings->bAllowJoinViaPresence			= bAllowJoinViaPresense;
		SessionSettings->bUseLobbiesIfAvailable			= bUseLobbiesIfAvailable;
		SessionSettings->bUseLobbiesVoiceChatIfAvailable= bUseLobbiesVoiceChatIfAvailable;

		
		SessionSettings->Set(SEARCH_KEYWORDS, SessionName.ToString(), EOnlineDataAdvertisementType::ViaOnlineService);

		Sessions->AddOnCreateSessionCompleteDelegate_Handle(FOnCreateSessionCompleteDelegate::CreateUObject(this, &USNOnlineSystem::OnCreateSessionComplete));
		// プレイヤーコントローラを取得
		APlayerController* PlayerController(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		
		SNPLUGIN_ASSERT(PlayerController != nullptr, TEXT("PlayerController is nullptr"));
		// ローカルプレイヤーを取得
		ULocalPlayer* LocalPlayer(PlayerController->GetLocalPlayer());
		
		if(LocalPlayer != nullptr){

			TSharedPtr<const FUniqueNetId> UniqueNetIdptr = LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId();
			
			bool bResult = Sessions->CreateSession(*UniqueNetIdptr, SessionName, *SessionSettings);

			if(bResult == true){
				
				SNPLUGIN_LOG(TEXT("Success to Create Session."))
				
				return true;
			} else {
				SNPLUGIN_ERROR(TEXT("CreateSession: Fail"));
			}
		}
	}
	
	return false;
}

//----------------------------------------------------------------------//
//
//! @brief セッションを検索
//
//----------------------------------------------------------------------//
void USNOnlineSystem::FindSession(){
	
	IOnlineSubsystem* const OnlineSubsystem = Online::GetSubsystem(GetWorld());
	
	SNPLUGIN_ASSERT(OnlineSubsystem != nullptr, TEXT("OnlineSubsystem is nullptr"));
	
	IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
	
	if(Sessions.IsValid()){
		
		SearchSettings = MakeShareable(new FOnlineSessionSearch());
		
		SNPLUGIN_ASSERT(SearchSettings != nullptr, TEXT("Failed to allocate Session Search Settings."));
		
		SearchSettings->QuerySettings.Set(SEARCH_PRESENCE, true, EOnlineComparisonOp::Equals);
		SearchSettings->QuerySettings.Set(SEARCH_LOBBIES, true, EOnlineComparisonOp::Equals);
		//SearchSettings->QuerySettings.Set(SEARCH_KEYWORDS, FString("Custom"), EOnlineComparisonOp::Equals);
		//SearchSettings->QuerySettings.Set(SETTING_CUSTOM, true, EOnlineComparisonOp::Equals);
		
		Sessions->AddOnFindSessionsCompleteDelegate_Handle(FOnFindSessionsCompleteDelegate::CreateUObject(this, &USNOnlineSystem::OnFindSessionsComplete));
		
		TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SearchSettings.ToSharedRef();
		// プレイヤーコントローラを取得
		APlayerController* PlayerController(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		
		SNPLUGIN_ASSERT(PlayerController != nullptr, TEXT("PlayerController is nullptr"));
		// ローカルプレイヤーを取得
		ULocalPlayer* LocalPlayer(PlayerController->GetLocalPlayer());
		
		if(LocalPlayer != nullptr){
			// NetIdを取得
			TSharedPtr<const FUniqueNetId> UniqueNetIdptr = LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId();
			// セッションの検索を開始
			bool bIsSuccess = Sessions->FindSessions(*UniqueNetIdptr, SearchSettingsRef);
		}
	}
}

//----------------------------------------------------------------------//
//
//! @brief セッションを終了
//
//----------------------------------------------------------------------//
void USNOnlineSystem::KillSession(){
	
	IOnlineSubsystem* const OnlineSubsystem = Online::GetSubsystem(GetWorld());
	
	SNPLUGIN_ASSERT(OnlineSubsystem != nullptr, TEXT("OnlineSubsystem is nullptr"));
	
	IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
	
	if(Sessions.IsValid()){
		// セッションを終了
		Sessions->DestroySession(SessionName);
	}
}


//----------------------------------------------------------------------//
//
//! @brief ログインが完了した際に呼ばれるデリゲート
//
//! @param LocalUserNum   ユーザー数
//! @param bWasSuccessful ログインが完了したかのフラグ
//! @param UserId         ユーザーID
//! @param Error          エラーの内容
//
//----------------------------------------------------------------------//
void USNOnlineSystem::OnLoginComplete(int32 LocalUserNum, bool bWasSuccessful, const FUniqueNetId& UserId, const FString& Error){
	
	if(bWasSuccessful == false){
		
		SNPLUGIN_ERROR(TEXT("Login Failed : [%s] : %s"), *UserId.ToString(), *Error);
		
		return;
	}
	
	IOnlineIdentityPtr Identity(Online::GetIdentityInterface(GetWorld()));
	
	if(Identity.IsValid()){
		
		APlayerController* PlayerController(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		
		SNPLUGIN_ASSERT(PlayerController != nullptr, TEXT("PlayerController is nullptr"));
		
		ULocalPlayer* LocalPlayer(PlayerController->GetLocalPlayer());
		
		if(LocalPlayer != nullptr){
			
			int Id = LocalPlayer->GetControllerId();
			
			FUniqueNetIdRepl uniqueId = PlayerController->PlayerState->GetUniqueId();
			
			uniqueId.SetUniqueNetId(FUniqueNetIdWrapper(LocalPlayer->GetCachedUniqueNetId()).GetUniqueNetId());
			
			PlayerController->PlayerState->SetUniqueId(uniqueId);
			
			ELoginStatus::Type Status = Identity->GetLoginStatus(Id);
			
			SNPLUGIN_LOG(TEXT("Login Status : %s"), ELoginStatus::ToString(Status));
		}
	}
}

//----------------------------------------------------------------------//
//
//! @brief セッション生成に成功した際に呼ばれるデリゲート
//
//! @param InSessionName  セッション名
//! @param bWasSuccessful セッション生成に成功したかどうかのフラグ
//
//----------------------------------------------------------------------//
void USNOnlineSystem::OnCreateSessionComplete(FName InSessionName, bool bWasSuccessful){
	
	if(bWasSuccessful == true){
		SNPLUGIN_LOG(TEXT("Create Session Succeed [%s]."), *InSessionName.ToString());
	} else {
		SNPLUGIN_ERROR(TEXT("Failed to Session Succeed [%s]."), *InSessionName.ToString());
	}

	OnCompleteHostSession.ExecuteIfBound(InSessionName, bWasSuccessful);
}

//----------------------------------------------------------------------//
//
//! @brief セッションの検索が完了した際に呼ばれるデリゲート
//
//! @param bWasSuccessful セッションの検索に成功したかのフラグ
//
//----------------------------------------------------------------------//
void USNOnlineSystem::OnFindSessionsComplete(bool bWasSuccessful){
	
	if(bWasSuccessful == true){
		
		SNPLUGIN_LOG(TEXT("Find Session: Success"));
		// ※エディタ同士の場合検索結果が0になり、セッション検索に失敗したことになります。
		//   スタンドアローン起動なら大丈夫です。
		if(SearchSettings->SearchResults.Num() == 0){
			SNPLUGIN_LOG(TEXT("No session found."));
		} else {
			
			const TCHAR* SessionId = *SearchSettings->SearchResults[0].GetSessionIdStr();
			// DISPLAY_LOG("Session ID: %s", SessionId);
			//JoinSession(SearchSettings->SearchResults[0]);
		}
	} else {
		// セッション検索失敗
		SNPLUGIN_LOG(TEXT("Find Session: Fail"));
	}

	OnCompleteFindSession.ExecuteIfBound(bWasSuccessful);
}


void USNOnlineSystem::JoinSession(FOnlineSessionSearchResult SearchResult){
	
	IOnlineSubsystem* const OnlineSubsystem = Online::GetSubsystem(GetWorld());
	
	if(OnlineSubsystem != nullptr){
		
		IOnlineSessionPtr Sessions(OnlineSubsystem->GetSessionInterface());
		
		if(Sessions.IsValid()){

			if(SearchResult.IsValid()){
				
				Sessions->AddOnJoinSessionCompleteDelegate_Handle(FOnJoinSessionCompleteDelegate::CreateUObject(this, &USNOnlineSystem::OnJoinSessionComplete));
				
				APlayerController* PlayerController(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				
				SNPLUGIN_ASSERT(PlayerController != nullptr, TEXT("PlayerController is nullptr"));
				
				ULocalPlayer* LocalPlayer(PlayerController->GetLocalPlayer());
				
				if(LocalPlayer != nullptr){
					
					TSharedPtr<const FUniqueNetId> UniqueNetIdptr = LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId();
					// セッションに参加
					Sessions->JoinSession(*UniqueNetIdptr, SessionName, SearchResult);
				}
			} else {
				SNPLUGIN_LOG(TEXT("Invalid session."));
			}
		}
	}
}

void USNOnlineSystem::OnJoinSessionComplete(FName InSessionName, EOnJoinSessionCompleteResult::Type Result){
	
	IOnlineSubsystem* const OnlineSubsystem = Online::GetSubsystem(GetWorld());
	
	if(OnlineSubsystem != nullptr){
		
		IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
		
		if(Sessions.IsValid()){
			
			if(Result == EOnJoinSessionCompleteResult::Success){
				// Client travel to the server
				FString ConnectString;
				
				if(Sessions->GetResolvedConnectString(SessionName, ConnectString)){
					
					UE_LOG_ONLINE_SESSION(Log, TEXT("Join session: traveling to %s"), *ConnectString);
					
					APlayerController* PlayerController(UGameplayStatics::GetPlayerController(GetWorld(), 0));
					
					SNPLUGIN_ASSERT(PlayerController != nullptr, TEXT("PlayerController is nullptr"));
					
					PlayerController->ClientTravel(ConnectString, TRAVEL_Absolute);
				}
			}
		}
	}

	OnCompleteJoinSession.ExecuteIfBound(InSessionName, Result == EOnJoinSessionCompleteResult::Success ? true : false);
}
