// Fill out your copyright notice in the Description page of Project Settings.


#include "System\SNOnlineGameModeBase.h"
#include "EngineUtils.h"
#include "SNDef.h"
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

	if(PlayerIDList.Contains(PlayerID) == false)
	{
		PlayerIDList.Add(PlayerID);
	}

	SNPLUGIN_LOG(TEXT("Init New Player Done."))
	
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

	SNPLUGIN_LOG(TEXT("Post Login."))
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
		int PlayerID = PlayerState->GetPlayerId();
		
		if(!StartPoints.IsEmpty()){

			if(PlayerIDList.Contains(PlayerID) == false)
			{
				PlayerIDList.Add(PlayerID);
			}
			
			int index = PlayerIDList.IndexOfByKey(PlayerID);

			if(index < StartPoints.Num())
			{
				return StartPoints[index];	
			}
		}
	}

	return nullptr;
}
