// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/System/CWGameMode.h"
#include "EngineUtils.h"
#include "Engine/PlayerStartPIE.h"
#include "GameFramework/PlayerState.h"

FString ACWGameMode::InitNewPlayer(APlayerController* NewPlayerController, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	FString Result = Super::InitNewPlayer(NewPlayerController, UniqueId, Options, Portal);
	
	return Result;
}

AActor* ACWGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	if(AActor* PlayerStart = ChoosePlayerStart(Player))
	{
		return PlayerStart;
	}
	
	return Super::ChoosePlayerStart_Implementation(Player);
}

void ACWGameMode::PostLogin(APlayerController* NewPlayer)
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

AActor* ACWGameMode::ChoosePlayerStart(AController* Player)
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
		if(PlayerState->IsOnlyASpectator())
		{
			if(!StartPoints.IsEmpty())
			{
				return StartPoints[FMath::RandRange(0, StartPoints.Num()-1)];
			}

		}
	}

	return nullptr;
}


