// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Character/Player/CWPlayerState.h"

#include "CW/CWDef.h"
#include "Net/UnrealNetwork.h"
#include "Utility/SNUtility.h"

void ACWPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACWPlayerState, bReadyToBattle)
}

void ACWPlayerState::SetReadyToBattle(bool bFlag)
{
	if(SNUtility::IsServer(GetWorld()) == false)
	{
		SendServerReadyToBattle(bFlag);
	} else
	{
		bReadyToBattle = bFlag;	
	}
}

void ACWPlayerState::SendServerReadyToBattle_Implementation(bool bFlag)
{
	bReadyToBattle = bFlag;

	CW_LOG(TEXT("ReadyToBattle is on in Server."));
}

