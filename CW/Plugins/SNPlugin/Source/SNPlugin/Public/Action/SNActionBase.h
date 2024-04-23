// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "InputActionValue.h"
#include "SNActionBase.generated.h"

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
class UEnhancedInputComponent;
class UInputAction;
class AActor;
struct FInputActionValue;

USTRUCT()
struct FInputActionValueProxy:public FInputActionValue
{
	GENERATED_BODY()

	FInputActionValueProxy():Super(){}
	
	FInputActionValueProxy(const FInputActionValue& InputActionValue):
	Super(InputActionValue.GetValueType(), Axis3D(InputActionValue[0], InputActionValue[1], InputActionValue[2]))
	{
		
	}
	FVector GetValue()
	{
		return Value;
	}

	EInputActionValueType GetType()
	{
		return ValueType;
	}
};
//----------------------------------------------------------------------//
//
//! @brief アクション用ベースクラス
//
//----------------------------------------------------------------------//
UCLASS()
class SNPLUGIN_API USNActionBase : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	// ISNPlayablePawnInterfaceのみExecActionを呼び出せるように。
	friend class ISNPlayablePawnInterface;
	
	//! @{@name デフォルトコンストラクタ
	USNActionBase();
	//! @}
	
	//! @{@name デストラクタ
	virtual ~USNActionBase();
	//! @}
	
	//! @{@name 初期化処理
	virtual void Initialize(UEnhancedInputComponent* InputComponent, const UInputAction* InputAction, UObject* Object);
	//! @}
	
	//! @{@name オーナーを設定
	void	SetOwner(AActor* Object) override ;
	//! @}
	
	//! @{@name 入力からのアクション
	void	InputAction(const FInputActionValue& InputActionValue);
	//! @}
	
	//! @{@name オーナーを取得
	template<class T>
	T* GetOwner();
	
	template<class T>
	const T* GetOwner() const ;
	//! @}
	
	//! @{@name アクション名の設定
	void	SetActionName(const FName& Name);
	//! @}
	
	//! @{@name アクション名を取得
	FName GetActionName() const ;
	//! @}
	
protected:
	
	
	//! @{@name 各アクションの実行処理
	virtual void ExecAction(const FInputActionValue& InputActionValue){};
	//! @}
	
private:
	
	//!< アクション名
	FName ActionName;
	
	//!< オーナー
	UObject*	Owner;
};

//----------------------------------------------------------------------//
//
//! @brief オーナーを設定
//
//! @param Object オーナーとなるオブジェクト
//
//----------------------------------------------------------------------//
FORCEINLINE void	USNActionBase::SetOwner(AActor* Object){
	
	Super::SetOwner(Object);
	
	Owner = Object;
}

//----------------------------------------------------------------------//
//
//! @brief アクション名の設定
//
//! @param Name アクション名
//
//----------------------------------------------------------------------//
FORCEINLINE void	USNActionBase::SetActionName(const FName& Name){
	ActionName = Name;
}

//----------------------------------------------------------------------//
//
//! @brief アクション名を取得
//
//! @retval アクション名
//
//----------------------------------------------------------------------//
FORCEINLINE FName USNActionBase::GetActionName() const {
	return ActionName;
}


//----------------------------------------------------------------------//
//
//! @brief オーナーを取得
//
//! @retval オーナーへのポインタ
//
//----------------------------------------------------------------------//
template<class T>
FORCEINLINE T* USNActionBase::GetOwner(){
	return Cast<T>(Owner);
}

//----------------------------------------------------------------------//
//
//! @brief オーナーを取得
//
//! @retval オーナーへのポインタ
//
//----------------------------------------------------------------------//
template<class T>
FORCEINLINE const T* USNActionBase::GetOwner() const {
	return Cast<T>(Owner);
}
