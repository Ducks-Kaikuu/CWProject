// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "InputMappingContext.h"
#include "SNPlayablePawnComponent.generated.h"

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
class USNInputConfig;

//----------------------------------------------------------------------//
//
//! @brief プレイヤブルキャラクターコンポーネント
//
//----------------------------------------------------------------------//
UCLASS(Blueprintable, Meta = (BlueprintSpawnableComponent))
class SNPLUGIN_API USNPlayablePawnComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()
	
public:
	
	//! @{@name デフォルトコンストラクタ
	USNPlayablePawnComponent(const FObjectInitializer& ObjectInitializer);
	//! @}
	
	//! @{@name 入力コンフィグを取得
	USNInputConfig* GetInputConfig();
	//! @}
	
	//! @{@name マッピングコンテキストを取得
	UInputMappingContext* GetInputMappingContext(FName name);
	//! @}
	
	//~ Begin IGameFrameworkInitStateInterface interface
	virtual FName GetFeatureName() const override { return FName(TEXT("Vehicle")); }
	virtual bool CanChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) const override;
	virtual void HandleChangeInitState(UGameFrameworkComponentManager* Manager, FGameplayTag CurrentState, FGameplayTag DesiredState) override;
	virtual void OnActorInitStateChanged(const FActorInitStateChangedParams& Params) override;
	virtual void CheckDefaultInitialization() override;
	//~ End IGameFrameworkInitStateInterface interface
	
protected:
		
	virtual void OnRegister() override;
	
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	
	//!< 入力コンフィグ
	UPROPERTY(EditDefaultsOnly, Meta = (TitleProperty = "Input Config"))
	TObjectPtr<USNInputConfig> InputConfig;
	
	//!< マッピングコンテキスト
	UPROPERTY(EditDefaultsOnly, Meta = (TitleProperty = "Input Context Map"))
	TMap<FName, TObjectPtr<UInputMappingContext>> InputMapContextMap;
};

//----------------------------------------------------------------------//
//
//! @brief 入力コンフィグを取得
//
//! @retval 入力コンフィグ
//
//----------------------------------------------------------------------//
FORCEINLINE USNInputConfig* USNPlayablePawnComponent::GetInputConfig() {
	return InputConfig;
}

//----------------------------------------------------------------------//
//
//! @brief マッピングコンテキストを取得
//
//! @param name コンテキスト名
//
//! @retval マッピングコンテキスト
//
//----------------------------------------------------------------------//
FORCEINLINE UInputMappingContext* USNPlayablePawnComponent::GetInputMappingContext(FName name){
	
	UInputMappingContext* InputMappingContext = (InputMapContextMap.Find(name) != nullptr) ? InputMapContextMap[name] : nullptr;
	
	return InputMappingContext;
}

