// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Character/Player/CWPlayerState.h"

#include "Net/UnrealNetwork.h"

void ACWPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACWPlayerState, bReadyToBattle)
}
