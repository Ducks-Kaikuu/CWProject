// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/SNPlayablePawnComponent.h"
#include "GameplayTags/SNGameplayTags.h"

#include "EnhancedInputSubsystems.h"
#include "OnlineSubsystemUtils.h"
#include "SNDef.h"
#include "Input/SNInputConfig.h"
#include "Input/SNInputManagerSubsystem.h"
#include "UserSettings/EnhancedInputUserSettings.h"

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//! @param ObjectInitializer イニシャライザ
//
//----------------------------------------------------------------------//
USNPlayablePawnComponent::USNPlayablePawnComponent(const FObjectInitializer& ObjectInitializer)
:Super(ObjectInitializer)
{
	
}

void USNPlayablePawnComponent::OnRegister(){
	
	Super::OnRegister();
	
	if(GetPawn<APawn>() != nullptr){
		RegisterInitStateFeature();
	}
}

void USNPlayablePawnComponent::BeginPlay(){
	
	Super::BeginPlay();
	
	BindOnActorInitStateChanged(GetFeatureName(), FGameplayTag(), false);
	
	ensure(TryToChangeInitState(SNGameplayTags::InitState_Spawned));
	// ...
	CheckDefaultInitialization();
}

void USNPlayablePawnComponent::CheckDefaultInitialization(){
	
	static const TArray<FGameplayTag> StateChain = { SNGameplayTags::InitState_Spawned, SNGameplayTags::InitState_DataAvailable, SNGameplayTags::InitState_DataInitialized};
	
	ContinueInitStateChain(StateChain);
}

bool USNPlayablePawnComponent::CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const {
	
	return true;
}

void USNPlayablePawnComponent::HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState){
	
	if((CurrentState == SNGameplayTags::InitState_DataAvailable)
	&& (DesiredState == SNGameplayTags::InitState_DataInitialized)){

		if(InputConfig != nullptr)
		{
			APawn* Pawn = GetPawn<APawn>();

			SNPLUGIN_ASSERT(Pawn != nullptr, TEXT("Failed to GetPawn"));
				
			InputConfig->InitializeInput(Pawn);
		}
	}
}

void USNPlayablePawnComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params){
	
}
