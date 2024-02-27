// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Action/CWCameraOperation.h"
#include "CW/CWDef.h"
#include "CW/Camera/CWPlayerCameraManager.h"
#include "CW/Player/CWPlayerController.h"

void UCWCameraOperation::ExecAction(const FInputActionValue& InputActionValue){
	
	Super::ExecAction(InputActionValue);

	ACWPlayerController* PlayerController = GetCWPlayerController();

	ACWPlayerCameraManager* CameraManager =Cast<ACWPlayerCameraManager>(PlayerController->PlayerCameraManager);

	if(CameraManager != nullptr)
	{
		
	}
}
