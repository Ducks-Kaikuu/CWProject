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
class UInputMappingContext;

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
	
	//!< ゲームプレイタグで実行するアクション
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "Action"))
	TSoftClassPtr<USNActionBase> ActionClass = nullptr;
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
	
	bool	InitializeInput(FName Name, UObject* OwnerObject);

	void SetEnabled(bool bEnabled);

	const FName& GetInputName() const ;
	
	const TSoftObjectPtr<UInputMappingContext>& GetInputMappingContext() const ;

	void Release();
	
private:
	
	//! @{@name ロード終了処理
	void FinishLoadAsset();
	//! @}
	
	UPROPERTY()
	FName InputName=NAME_None;
	
	UPROPERTY(EditAnywhere, Category="Input")
	TSoftObjectPtr<UInputMappingContext> InputMappingContext = nullptr;

	//!< 入力アクション用リスト
	UPROPERTY(EditDefaultsOnly, Meta = (TitleProperty = "InputAction"), Category="Input")
	TArray<FSNInputAction> InputActionList;
	
	UPROPERTY()
	TObjectPtr<UObject> Owner;
	
	TSharedPtr<FStreamableHandle> StreamableHandle;
};

FORCEINLINE const FName& USNInputConfig::GetInputName() const
{
	return InputName;
} 
FORCEINLINE const TSoftObjectPtr<UInputMappingContext>& USNInputConfig::GetInputMappingContext() const
{
	return InputMappingContext;
} 