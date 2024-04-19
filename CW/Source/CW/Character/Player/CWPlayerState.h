// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/SNPlayerState.h"
#include "CWPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CW_API ACWPlayerState : public ASNPlayerState
{
	GENERATED_BODY()

public:

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void SetReadyToBattle(bool bFlag);

	bool IsReadyToBattle() const ;
	
private:

	UFUNCTION(Server, Reliable)
	void SendServerReadyToBattle(bool bFlag);
	
	UPROPERTY(Replicated)
	bool bReadyToBattle = false;
};

FORCEINLINE bool ACWPlayerState::IsReadyToBattle() const
{
	return bReadyToBattle;
}


