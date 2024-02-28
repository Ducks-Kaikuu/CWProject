// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CWPlayerCameraManager.generated.h"

class ACWCameraActorBase;
/**
 * 
 */
UCLASS()
class CW_API ACWPlayerCameraManager : public APlayerCameraManager
{
	GENERATED_BODY()

protected:

	ACWPlayerCameraManager(const FObjectInitializer& Initializer);
	
	void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere, Category="CW|Camera")
	TMap<FName, TSoftClassPtr<ACWCameraActorBase>> CameraClassMap;

	UPROPERTY()
	TMap<FName, TObjectPtr<ACWCameraActorBase>> CameraInstanseMap;

	FName CurrentCamera;
};
