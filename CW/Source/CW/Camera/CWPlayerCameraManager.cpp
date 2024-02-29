// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Camera/CWPlayerCameraManager.h"

#include "CWCameraActorBase.h"
#include "CW/CWDef.h"

ACWPlayerCameraManager::ACWPlayerCameraManager(const FObjectInitializer& Initializer)
:Super(Initializer)
,CurrentCamera(NAME_None)
{
}

void ACWPlayerCameraManager::BeginPlay(){
	
	Super::BeginPlay();
	
	UWorld* World(GetWorld());
	
	if(World != nullptr){
		
		for(auto Object: CameraClassMap){
			
			ACWCameraActorBase* CameraInstance = nullptr;
			
			UClass* Class(Object.Value.LoadSynchronous());
			
			if(Class != nullptr){
				
				CameraInstance = Cast<ACWCameraActorBase>(World->SpawnActor(Class));
				
				CameraInstanseMap.Add(Object.Key, CameraInstance);
				
				if(CurrentCamera == NAME_None)
				{
					CurrentCamera = Object.Key;
				}
			}
			
			CW_ASSERT(CameraInstance != nullptr, TEXT("Failed to create camera instance : %s"), *Object.Key.ToString());
		}
	}
	
	SetViewTarget(CameraInstanseMap[CurrentCamera]);
}
