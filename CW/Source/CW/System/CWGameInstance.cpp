﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/System/CWGameInstance.h"
#include "GameplayTags/SNGameplayTags.h"

#include "Components/GameFrameworkComponentManager.h"

UCWGameInstance* GetCWGameInstance(){
	
	if(UWorld* pPrimaryWorld = GetPrimaryWorld()){
		return Cast<UCWGameInstance>(pPrimaryWorld->GetGameInstance());
	}
	
	return nullptr;
}
//----------------------------------------------------------------------//
//
//! @brief 初期化処理
//
//----------------------------------------------------------------------//
void UCWGameInstance::Init(){
	
	Super::Init();
	
	// 
	UGameFrameworkComponentManager* ComponentManager = GetSubsystem<UGameFrameworkComponentManager>(this);
	
	if(ensure(ComponentManager)){
		ComponentManager->RegisterInitState(SNGameplayTags::InitState_Spawned        , false, FGameplayTag());
		ComponentManager->RegisterInitState(SNGameplayTags::InitState_DataAvailable  , false, SNGameplayTags::InitState_Spawned);
		ComponentManager->RegisterInitState(SNGameplayTags::InitState_DataInitialized, false, SNGameplayTags::InitState_DataAvailable);
	}
}
