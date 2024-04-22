// Fill out your copyright notice in the Description page of Project Settings.
#include "Input/SNInputConfig.h"
#include "SNDef.h"
#include "Utility/SNUtility.h"
#include "Input/SNInputManagerSubsystem.h"
#include "Action/SNActionBase.h"

#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"


//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//! @param ObjectInitializer イニシャライザ
//
//----------------------------------------------------------------------//
USNInputConfig::USNInputConfig(const FObjectInitializer& ObjectInitializer){
	
}

bool	USNInputConfig::InitializeInput(FName InputName, UObject* OwnerObject){

	SNPLUGIN_ASSERT(OwnerObject != nullptr, TEXT("Should set Input Action Owner."));
	
	Owner = OwnerObject;

	Name = InputName;
	
	UGameInstance* GameInstance(SNUtility::GetGameInstance<UGameInstance>());
	
	SNPLUGIN_ASSERT(GameInstance != nullptr, TEXT("GameInstance is nullptr"));
	
	USNInputManagerSubsystem* InputManagerSubsystem(GameInstance->GetSubsystem<USNInputManagerSubsystem>());
	
	SNPLUGIN_ASSERT(InputManagerSubsystem != nullptr, TEXT("InputManagerSubsystem is nullptr."));
	
	UInputMappingContext* InputMappingContextInstance(InputMappingContext.LoadSynchronous());
	
	SNPLUGIN_ASSERT(InputMappingContextInstance != nullptr, TEXT("InputMappingContext is nullptr."));
	
	InputManagerSubsystem->AddInputContext(Name, InputMappingContextInstance);
	
	TArray<FSoftObjectPath> assetList;
	
	for(auto& action:InputActionList){
		
		assetList.Add(action.ActionClass.ToSoftObjectPath());
	}
	
	StreamableHandle = SNUtility::RequestAsyncLoad(assetList, this, &USNInputConfig::FinishLoadAsset);
	
	return true;
}

void	USNInputConfig::FinishLoadAsset(){
	
	UEnhancedInputComponent* InputComponent = nullptr;
	
	APawn* Pawn = Cast<APawn>(Owner);
	
	if(Pawn != nullptr){
		InputComponent = Cast<UEnhancedInputComponent>(Pawn->InputComponent);
	} else {
		
		APlayerController* PlayerController(SNUtility::GetPlayerController<APlayerController>());
		
		SNPLUGIN_ASSERT(PlayerController != nullptr, TEXT("PlayerController is nullptr."));
		
		InputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
	}
		
	TArray<UObject*> ObjectList;
	
	StreamableHandle->GetLoadedAssets(ObjectList);
	
	int Count = 0;
	
	for(auto& Object: ObjectList){
		
		UClass* ClassPtr = Cast<UClass>(Object);
		
		if(ClassPtr != nullptr){
			
			FSNInputAction& Input(InputActionList[Count]);
			
			Input.Action = NewObject<USNActionBase>(Owner, ClassPtr);
			
			if(Input.Action != nullptr){
				Input.Action->Initialize(InputComponent, Input.InputAction.Get(), Owner);
			}
		}
		
		++Count;
	}
}

void USNInputConfig::SetEnabled(bool bEnabled)
{
	UGameInstance* GameInstance(SNUtility::GetGameInstance<UGameInstance>());
	
	SNPLUGIN_ASSERT(GameInstance != nullptr, TEXT("GameInstance is nullptr"));
	
	USNInputManagerSubsystem* InputManagerSubsystem(GameInstance->GetSubsystem<USNInputManagerSubsystem>());
	
	if(InputManagerSubsystem != nullptr)
	{
		if(bEnabled == true){
			InputManagerSubsystem->EnableInputMapping(GetKey());
		} else {
			InputManagerSubsystem->DisableInputMapping(GetKey());
		}
	}
}

void USNInputConfig::Release()
{
	UGameInstance* GameInstance(SNUtility::GetGameInstance<UGameInstance>());
	
	SNPLUGIN_ASSERT(GameInstance != nullptr, TEXT("GameInstance is nullptr"));
	
	USNInputManagerSubsystem* InputManagerSubsystem(GameInstance->GetSubsystem<USNInputManagerSubsystem>());
	
	if(InputManagerSubsystem != nullptr)
	{
		InputManagerSubsystem->RemoveInputContext(GetKey());
	}
}

