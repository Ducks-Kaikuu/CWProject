// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "SNOnlineGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SNPLUGIN_API ASNOnlineGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:

	virtual void PostLogin(APlayerController* NewPlayer) override;

	AActor* ChoosePlayerStart(AController* Player);

	virtual void InitGameState() override;
	
protected:

	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	
	virtual FString InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal) override;

private:

	UPROPERTY(EditAnywhere, Category="Setting")
	bool bEnabledOnline = false;
	
	TArray<int> PlayerIDList;
	
	TArray<TObjectPtr<AActor>> PlayerStartList;
};
