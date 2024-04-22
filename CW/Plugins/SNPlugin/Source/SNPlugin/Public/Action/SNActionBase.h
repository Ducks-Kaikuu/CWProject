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
	
	//! @{@name デフォルトコンストラクタ
	USNActionBase();
	//! @}
	
	//! @{@name デストラクタ
	virtual ~USNActionBase();
	//! @}
	
	virtual void Initialize(UEnhancedInputComponent* InputComponent, const UInputAction* InputAction, UObject* Object);
	
	//! @{@name オーナーを設定
	void	SetOwner(AActor* Object) override ;
	//! @}
	
	void	SetName(const FName& name);
	
	//! @{@name 入力からのアクション
	void	InputAction(const FInputActionValue& InputActionValue);
	//! @}
	
	//! @{@name オーナーを取得
	template<class T>
	T* GetOwner();
	
	template<class T>
	const T* GetOwner() const ;
	//! @}
#if 0
	//! @{@name 名前を取得
	FName GetName() const ;
	//! @}
#endif
protected:
	
	
	//! @{@name 各アクションの実行処理
	virtual void ExecAction(const FInputActionValue& InputActionValue){};
	//! @}
	
	UFUNCTION(Server, Reliable)
	void InputAction_OnServer(const FInputActionValue& InputActionValue);
	
private:
	
	//!< アクション名
	FName Name;
	
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
inline void	USNActionBase::SetOwner(AActor* Object){
	
	Super::SetOwner(Object);
	
	Owner = Object;
}

inline void	USNActionBase::SetName(const FName& name){
	Name = name;
}

//----------------------------------------------------------------------//
//
//! @brief オーナーを取得
//
//! @retval オーナーへのポインタ
//
//----------------------------------------------------------------------//
template<class T>
inline T* USNActionBase::GetOwner(){
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
inline const T* USNActionBase::GetOwner() const {
	return Cast<T>(Owner);
}
#if 0
//----------------------------------------------------------------------//
//
//! @brief 名前を取得
//
//! @retval 名前
//
//----------------------------------------------------------------------//
inline FName USNActionBase::GetName() const {
	return Name;
}
#endif
