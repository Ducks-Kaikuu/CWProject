// Fill out your copyright notice in the Description page of Project Settings.


#include "System\SNOnlineGameModeBase.h"
#include "EngineUtils.h"
#include "Engine/PlayerStartPIE.h"
#include "GameFramework/PlayerState.h"

void ASNOnlineGameModeBase::InitGameState()
{
	Super::InitGameState();

	PlayerIDList.Empty();
}

FString ASNOnlineGameModeBase::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	FString Result = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);

	int PlayerID = NewPlayerController->PlayerState->GetPlayerId();

	PlayerIDList.Add(PlayerID);

	return Result;
}

void ASNOnlineGameModeBase::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	UWorld* World(GetWorld());

	if(World != nullptr)
	{
		for(TActorIterator<APlayerStart> It(World) ; It; ++It)
		{
			if(APlayerStart* PlayerStart = *It)
			{
				PlayerStartList.Add(PlayerStart);
			}
		}
	}
}

AActor* ASNOnlineGameModeBase::ChoosePlayerStart_Implementation(AController* Player)
{
	if(AActor* PlayerStart = ChoosePlayerStart(Player))
	{
		return PlayerStart;
	}

	return Super::ChoosePlayerStart_Implementation(Player);
}


AActor* ASNOnlineGameModeBase::ChoosePlayerStart(AController* Player)
{
	TArray<APlayerStart*> StartPoints;
	
	for(auto It=PlayerStartList.CreateIterator() ; It; ++It)
	{
		if(APlayerStart* Start = Cast<APlayerStart>((*It).Get()))
		{
			StartPoints.Add(Start);
		} else
		{
			It.RemoveCurrent();
		}
	}

	if(APlayerState* PlayerState = Player->GetPlayerState<APlayerState>())
	{
		if(!StartPoints.IsEmpty())
		{
			return StartPoints[PlayerState->GetPlayerId()];
		}
	}

	return nullptr;
}
