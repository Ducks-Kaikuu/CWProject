// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Camera/CWRearCameraActorBase.h"
#include "CWBattleCameraActor.generated.h"

//----------------------------------------------------------------------//
//
//! @brief バトルカメラアクター
//
//----------------------------------------------------------------------//
UCLASS()
class CW_API ACWBattleCameraActor : public ACWRearCameraActorBase
{
	GENERATED_BODY()
	
public:
	
	//! @{@name カメラのローテーション情報を取得
	FRotator GetCameraRotator() const ;
	//! @}
	
	//! @{@name カメラのローテーション情報を設定
	void SetCameraRotator(const FRotator& Rotator);public:
	//! @}
	
	//! @{@name 入力時のX方向の移動スピードを取得
	float GetXAxisSpeed() const ;
	//! @}
	
	//! @{@name 入力時のY方向の移動スピードを取得
	float GetYAxisSpeed() const ;
	//! @}
	
protected:

	void Tick(float DeltaSeconds) override;
	
private:
	
	//!< アタッチするボーン名
	UPROPERTY(EditAnyWhere, Category="CW|Camera|Parameter")
	FName BoneName=NAME_None;
	
	//!< ターゲットからのオフセット情報
	UPROPERTY(EditAnyWhere, Category="CW|Camera|Parameter")
	FVector TargetOffset=FVector(845.0f, 0.0f, 300.0f);
	
	//!< 車をフォーカスしたカメラ
	UPROPERTY(EditAnywhere, Category="CW|Camera|Parameter")
	bool bCarFocusedCamera = false;
	
	//!< 操作時のスピード
	UPROPERTY(EditAnywhere, Category="CW|Camera|Parameter")
	float XAxisSpeed = 1.0f;
	
	//!< 操作時のスピード
	UPROPERTY(EditAnywhere, Category="CW|Camera|Parameter")
	float YAxisSpeed = 1.0f;
	
	UPROPERTY(EditAnywhere, Category="CW|Camera|Parameter")
	float FocuedCameraHeight = 200.0f;
	
	//!< カメラの回転情報
	UPROPERTY()
	FRotator CameraRotate = FRotator::ZeroRotator;
};

//----------------------------------------------------------------------//
//
//! @brief カメラのローテーション情報を取得
//
//! @retval カメラのローテーション情報
//
//----------------------------------------------------------------------//
FORCEINLINE FRotator ACWBattleCameraActor::GetCameraRotator() const {
	return CameraRotate;
}

//----------------------------------------------------------------------//
//
//! @brief カメラのローテーション情報を設定
//
//! @param Rotator カメラのローテーション情報
//
//----------------------------------------------------------------------//
FORCEINLINE void ACWBattleCameraActor::SetCameraRotator(const FRotator& Rotator){
	CameraRotate = Rotator;
}

//----------------------------------------------------------------------//
//
//! @brief 入力時のX方向の移動スピードを取得
//
//! @retval 入力時のX方向の移動スピード
//
//----------------------------------------------------------------------//
FORCEINLINE float ACWBattleCameraActor::GetXAxisSpeed() const {
	return XAxisSpeed;
}

//----------------------------------------------------------------------//
//
//! @brief 入力時のY方向の移動スピードを取得
//
//! @retval 入力時のY方向の移動スピード
//
//----------------------------------------------------------------------//
FORCEINLINE float ACWBattleCameraActor::GetYAxisSpeed() const {
	return YAxisSpeed;
}
