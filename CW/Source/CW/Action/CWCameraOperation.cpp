// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Action/CWCameraOperation.h"
#include "CW/Vehicle/CWWheeledVehiclePawn.h"

#include "Camera/CameraComponent.h"
#include "InputActionValue.h"


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
		
		UCameraComponent* CamComponent = Cast<UCameraComponent>(Vehicle->GetComponentByClass(UCameraComponent::StaticClass()));
		
		if(CamComponent != nullptr){
			
			UpdateCarFocusedCamera(CamComponent, InputActionValue);
		}
	}
}

void UCWCameraOperation::UpdateCarFocusedCamera(UCameraComponent* CamComponent, const FInputActionValue& InputActionValue){
	
	const FInputActionValue::Axis2D Axis(InputActionValue.Get<FInputActionValue::Axis2D>());
	
	FRotator rot(CamComponent->GetRelativeRotation());
	
	rot.Yaw   += (FMath::Abs(Axis.X) < 0.01f) ? 0.0f : Axis.X;
	rot.Pitch += (FMath::Abs(Axis.Y) < 0.01f) ? 0.0f : Axis.Y;
	
	rot.Pitch = FMath::Clamp(rot.Pitch, -60.0f, 75.0);
	
	CamComponent->SetRelativeRotation(rot);
}
