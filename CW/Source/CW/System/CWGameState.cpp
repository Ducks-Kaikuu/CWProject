// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/System/CWGameState.h"

#include "CW/CWDef.h"
#include "CW/System/CWGameInstance.h"
#include "CW/Character/Player/CWPlayerState.h"
#include "Online/SNOnlineSystem.h"

bool ACWGameState::IsReadyToBattle() const
{
	int Count = GetReadyToBattleCount();

	UCWGameInstance* GameInstance(GetCWGameInstance());

	CW_ASSERT(GameInstance != nullptr, TEXT("GameInstance is nullptr."));

	if(GameInstance->GetOnlineSystem()->GetMaxPlayerNum() == Count)
	{
		return true;
	}

	return false;
}

int ACWGameState::GetReadyToBattleCount() const
{
	int Count = 0;
	
	for(auto& Player:PlayerArray)
	{
		ACWPlayerState* PlayerState(Cast<ACWPlayerState>(Player));

		if((PlayerState != nullptr) && (PlayerState->IsReadyToBattle()))
		{
			Count++;
		}
	}

	return Count;
}

