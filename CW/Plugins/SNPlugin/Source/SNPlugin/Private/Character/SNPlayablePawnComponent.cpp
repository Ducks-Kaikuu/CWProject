// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/SNPlayablePawnComponent.h"
#include "GameplayTags/SNGameplayTags.h"

#include "Components/GameFrameworkComponentDelegates.h"
#include "EnhancedInputSubsystems.h"
#include "OnlineSubsystemUtils.h"
#include "SNDef.h"
#include "Character/SNPlayerController.h"
#include "Input/SNInputConfig.h"
#include "Input/SNInputManagerSubsystem.h"
#include "UserSettings/EnhancedInputUserSettings.h"
#include "Utility/SNUtility.h"

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

void USNPlayablePawnComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UnregisterInitStateFeature();
	
	Super::EndPlay(EndPlayReason);

	InputConfig->Release();
}


void USNPlayablePawnComponent::CheckDefaultInitialization(){
	
	static const TArray<FGameplayTag> StateChain = { SNGameplayTags::InitState_Spawned, SNGameplayTags::InitState_DataAvailable, SNGameplayTags::InitState_DataInitialized, SNGameplayTags::InitState_GameplayReady};
	
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

			ASNPlayerController* PlayerController(SNUtility::GetPlayerController<ASNPlayerController>());
			
			if(PlayerController != nullptr)
			{
				PlayerController->EnabledInputType(FName(TEXT("Battle")), true);
			}
#if 0
			if(Pawn->InputComponent != nullptr){

				SNPLUGIN_LOG(TEXT("Initialize Input.[%s]"), *AActor::GetDebugName(Pawn));
				
				InputConfig->InitializeInput(Pawn);

				InputConfig->SetEnabled(true);

				OnCompleteInitInput.ExecuteIfBound(InputConfig->GetKey());
			} else
			{
				SNPLUGIN_LOG(TEXT("Input Initialize is Failed.[%s]"), *AActor::GetDebugName(Pawn));
			}
#endif

		}
	}
}

void USNPlayablePawnComponent::OnActorInitStateChanged(const FActorInitStateChangedParams& Params){
	
	if (Params.FeatureName == FName(TEXT("Vehicle")))
	{
		if (Params.FeatureState == SNGameplayTags::InitState_DataInitialized)
		{
			// If the extension component says all all other components are initialized, try to progress to next state
			CheckDefaultInitialization();
		}
	}
}
