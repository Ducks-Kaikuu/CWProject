// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Scene/StateTree/CWSceneTaskBase.h"
#include "CWMatchingSceneBase.generated.h"

/**
 * 
 */
UCLASS()
class CW_API UCWMatchingSceneBase : public UCWSceneTaskBase
{
	GENERATED_BODY()

public:
	
	static void SetSessionName(const FName& Name);

	static FName GetSessionName();

protected:
	bool bExit = false;
	
private:
	static FName MatchingSessionName;
};

FORCEINLINE void UCWMatchingSceneBase::SetSessionName(const FName& Name)
{
	MatchingSessionName = Name;
}

FORCEINLINE FName UCWMatchingSceneBase::GetSessionName()
{
	return MatchingSessionName;
}


