// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "Engine/AssetManager.h"
#include "InputTriggers.h"
#include "SNInputConfig.generated.h"

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
class UInputAction;
class USNActionBase;
class UEnhancedInputComponent;

//----------------------------------------------------------------------//
//
//! @brief 入力アクションの設定
//
//----------------------------------------------------------------------//
USTRUCT(BlueprintType)
struct FSNInputAction{
	
	GENERATED_BODY()
	
public:
	
	//!< アクションへのポインタ
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<const UInputAction> InputAction = nullptr;
	
	//!< ゲームプレイタグ
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
	
	//!< ゲームプレイタグで実行するアクション
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Action"))
	TSoftClassPtr<USNActionBase> ActionClass = nullptr;
	
	UPROPERTY()
	TObjectPtr<USNActionBase> Action=nullptr;
	
	void BindActionForInput(UEnhancedInputComponent* InputComponent, ETriggerEvent TriggerEvent);
};

//----------------------------------------------------------------------//
//
//! @brief 入力制御用のコンフィグ
//
//----------------------------------------------------------------------//
UCLASS()
class SNPLUGIN_API USNInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	
	//! @{@name デフォルトコンストラクタ
	USNInputConfig(const FObjectInitializer& ObjectInitializer);
	//! @}
	
	bool	InitializeInput(AActor* OwnerActor);
	
	//!< 入力アクション用リスト
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FSNInputAction> InputActionList;
	
	UPROPERTY()
	TObjectPtr<AActor> Owner;
	
private:
	
	//! @{@name ロード終了処理
	void FinishLoadAsset();
	//! @}
	
	TSharedPtr<FStreamableHandle> StreamableHandle;
};
