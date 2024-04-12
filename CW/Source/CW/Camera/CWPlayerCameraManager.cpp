// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Camera/CWPlayerCameraManager.h"

#include "CWCameraActorBase.h"
#include "CW/CWDef.h"
#include "Kismet/KismetSystemLibrary.h"

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

void ACWPlayerCameraManager::SetViewTarget(AActor* NewViewTarget, FViewTargetTransitionParams TransitionParams)
{
	APlayerController* PlayerController = GetOwningPlayerController();

	ACWCameraActorBase* Camera(Cast<ACWCameraActorBase>(NewViewTarget));
	// Cameraのベースクラスにキャストできない場合はターゲットに設定しない。
	// 初期化の順番によってPawnなどもここに飛んでくるため。
	if((PlayerController != nullptr) && (Camera != nullptr))
	{
		Super::SetViewTarget(NewViewTarget, TransitionParams);
	}
}
