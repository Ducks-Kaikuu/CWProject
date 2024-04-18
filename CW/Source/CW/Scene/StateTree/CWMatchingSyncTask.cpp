// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Scene/StateTree/CWMatchingSyncTask.h"

#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"
#include "OnlineSubsystemUtils.h"
#include "SNDef.h"
#include "CW/CWDef.h"
#include "CW/Character/Player/CWPlayerState.h"
#include "CW/System/CWGameState.h"
#include "CW/UI/Widget/CWButton.h"
#include "CW/UI/Widget/Matching/CWMatchingSyncMenu.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Utility/SNUtility.h"

void UCWMatchingSyncTask::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	
}

EStateTreeRunStatus UCWMatchingSyncTask::Tick(FStateTreeExecutionContext& Context, const float DeltaTime)
{
	EStateTreeRunStatus Result = Super::Tick(Context, DeltaTime);

	if(SNUtility::IsServer(GetWorld()))
	{
		ACWGameState* GameState(Cast<ACWGameState>(GetWorld()->GetGameState()));

		if(GameState != nullptr)
		{
			if(GameState->IsReadyToBattle() == true)
			{
				if(BattleMap.IsNull() == false)
				{
					UGameplayStatics::OpenLevel(GetWorld(), *BattleMap.GetAssetName(), true, "listen");
				}
				FinishTask();

				return EStateTreeRunStatus::Succeeded;
			}
		}
	}
#if 0
	IOnlineSubsystem* const OnlineSubsystem = Online::GetSubsystem(GetWorld());
	
	SNPLUGIN_ASSERT(OnlineSubsystem != nullptr, TEXT("OnlineSubsystem is nullptr"));
	
	IOnlineSessionPtr Sessions = OnlineSubsystem->GetSessionInterface();
	
	if(Sessions.IsValid())
	{
		EOnlineSessionState::Type Type = Sessions->GetSessionState(UCWMatchingSceneBase::GetSessionName());

		//CW_LOG(TEXT("Update."));
	}
#endif
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

	APlayerController* PlayerController(SNUtility::GetPlayerController<APlayerController>());

	CW_ASSERT(PlayerController != nullptr, TEXT("PlayerController is nullptr."));
	
	if((BattleMap.IsNull() == false) && ((PlayerController->GetNetMode() == NM_ListenServer) || (PlayerController->GetNetMode() == NM_Standalone)))
	{
		UGameplayStatics::OpenLevel(GetWorld(), *BattleMap.GetAssetName(), true, "listen");
	}
}

void UCWMatchingSyncTask::HudPostLoad()
{
	UCWMatchingSyncMenu* Menu = Cast<UCWMatchingSyncMenu>(GetHud());

	if(Menu != nullptr)
	{
		Menu->SetSessionName(UCWMatchingSceneBase::GetSessionName());

		if(UCWButton* Button = Menu->GetStartButton())
		{
			Button->OnClickedDelegate.AddDynamic(this, &UCWMatchingSyncTask::OnCreateButtonClicked);
		}
	}
}

void UCWMatchingSyncTask::OnCreateButtonClicked(UCWButton* Button)
{
	APlayerController* PlayerController(SNUtility::GetPlayerController<APlayerController>());

	CW_ASSERT(PlayerController != nullptr, TEXT("PlayerController is nullptr."));

	CW_ASSERT(PlayerController->IsLocalController() == true, TEXT("PlayerController is not local."));

	ACWPlayerState* PlayerState(PlayerController->GetPlayerState<ACWPlayerState>());

	if(PlayerState != nullptr)
	{
		PlayerState->SetReadyToBattle(true);
	}
	if(BattleMap.IsNull() == false)
	{
		//UGameplayStatics::OpenLevel(GetWorld(), *BattleMap.GetAssetName(), true, "listen");
		
	}	
}


