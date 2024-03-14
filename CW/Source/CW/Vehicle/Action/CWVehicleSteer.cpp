// Fill out your copyright notice in the Description page of Project Settings.

#include "CW/Vehicle/Action/CWVehicleSteer.h"

#include "InputActionValue.h"
#include "CW/Vehicle/CWWheeledVehiclePawn.h"

void UCWVehicleSteer::ExecAction(const FInputActionValue& InputActionValue){
	
	Super::ExecAction(InputActionValue);
	
	ACWWheeledVehiclePawn* Pawn = GetOwner<ACWWheeledVehiclePawn>();
	
	if(Pawn != nullptr){
		
		float xAxis = FMath::Abs(InputActionValue[0]) < 0.01f ? 0.0f : InputActionValue[0];
		float yAxis = FMath::Abs(InputActionValue[1]) < 0.01f ? 0.0f : InputActionValue[1];
		
		Pawn->SetSteer(xAxis, yAxis);
	}
}
