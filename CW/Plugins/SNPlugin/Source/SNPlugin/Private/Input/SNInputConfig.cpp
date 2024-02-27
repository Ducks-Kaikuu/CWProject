// Fill out your copyright notice in the Description page of Project Settings.
#include "Input/SNInputConfig.h"
#include "SNDef.h"
#include "Utility/SNUtility.h"
#include "Action/SNActionBase.h"
#include "Character/SNPlayablePawnComponent.h"
#include "EnhancedInputComponent.h"

//----------------------------------------------------------------------//
//
//! @brief アクションを入力コンポーネントにバインド
//
//! @param InputComponent 入力コンポーネント
//! @param TriggerEvent   トリガーイベント
//
//----------------------------------------------------------------------//
void FSNInputAction::BindActionForInput(UEnhancedInputComponent* InputComponent, ETriggerEvent TriggerEvent){
	
	if(Action == nullptr){
		
		SNPLUGIN_WARNING(TEXT("Input Action Object does not set\n"));
		
		return;
	}
	
	InputComponent->BindAction(InputAction.Get(), TriggerEvent, Action.Get(), &USNActionBase::InputAction);
}

//----------------------------------------------------------------------//
//
//! @brief デフォルトコンストラクタ
//
//! @param ObjectInitializer イニシャライザ
//
//----------------------------------------------------------------------//
USNInputConfig::USNInputConfig(const FObjectInitializer& ObjectInitializer){
	
}

bool	USNInputConfig::InitializeInput(AActor* OwnerActor){
	
	Owner = OwnerActor;
	
	TArray<FSoftObjectPath> assetList;
	
	for(auto& action:InputActionList){
		
		assetList.Add(action.ActionClass.ToSoftObjectPath());
	}
	
	StreamableHandle = SNUtility::RequestAsyncLoad(assetList, this, &USNInputConfig::FinishLoadAsset);
	
	return true;
}

void	USNInputConfig::FinishLoadAsset(){
	
	APawn* Pawn = Cast<APawn>(Owner);
	
	check(Pawn != nullptr);
	
	UEnhancedInputComponent* InputComponent = Cast<UEnhancedInputComponent>(Pawn->InputComponent);
	
	check(InputComponent != nullptr);
	
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
