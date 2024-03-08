// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Action/CWCameraOperation.h"
#include "CW/Vehicle/CWWheeledVehiclePawn.h"

#include "Camera/CameraComponent.h"
#include "InputActionValue.h"
#include "CW/Camera/CWBattleCameraActor.h"
#include "Utility/SNUtility.h"


UCWCameraOperation::UCWCameraOperation()
:Super()
,CameraRotation(FRotator::ZeroRotator)
{
	
}

//----------------------------------------------------------------------//
//
//! @brief 入力時のアクション
//
//! @param InputActionValue 入力された値
//
//----------------------------------------------------------------------//
void UCWCameraOperation::ExecAction(const FInputActionValue& InputActionValue){
	
	Super::ExecAction(InputActionValue);
	
	ACWWheeledVehiclePawn* Vehicle = GetOwner<ACWWheeledVehiclePawn>();
	
	if(Vehicle != nullptr){
		
		UpdateCarFocusedCamera(InputActionValue);
	}
}

void UCWCameraOperation::UpdateCarFocusedCamera(const FInputActionValue& InputActionValue){
	
	const FInputActionValue::Axis2D Axis(InputActionValue.Get<FInputActionValue::Axis2D>());
	// 現状のカメラを取得
	ACWBattleCameraActor* CameraActor(SNUtility::GetCurrentCameraActor<ACWBattleCameraActor>());
	// バトルカメラ出ない場合は処理をしない
	if(CameraActor != nullptr){
		
		float Yaw  (FMath::Abs(Axis.X) < 0.05f ? 0.0f : Axis.X);
		float Pitch(FMath::Abs(Axis.Y) < 0.05f ? 0.0f : Axis.Y);
		
		Yaw   *= CameraActor->GetXAxisSpeed();
		Pitch *= CameraActor->GetYAxisSpeed();
		
		FRotator rot(CameraActor->GetCameraRotator());
		
		rot.Yaw   += Yaw;
		rot.Pitch += Pitch;
		
		rot.Pitch = FMath::Clamp(rot.Pitch, -60.0f, 75.0);
		
		CameraActor->SetCameraRotator(rot);
	}
}
