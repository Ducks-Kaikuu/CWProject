// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CWGameMode.generated.h"

/**
 * 
 */
UCLASS()
class CW_API ACWGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

	virtual void PostLogin(APlayerController* NewPlayer) override;

	AActor* ChoosePlayerStart(AController* Player);
	
protected:

	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;

private:
	TArray<TObjectPtr<AActor>> PlayerStartList;
};
