// Fill out your copyright notice in the Description page of Project Settings.

#include "CW/Action/CWVehicleSteer.h"

void UCWVehicleSteer::ExecAction(const FInputActionValue& InputActionValue){
	
	Super::ExecAction(InputActionValue);
	
	ACWWheeledVehiclePawn* Pawn = GetOwner<ACWWheeledVehiclePawn>();
	
	if(Pawn != nullptr){
		
		float xAxis = InputActionValue[0];
		float yAxis = InputActionValue[1];
		
		Pawn->SetSteer(xAxis, yAxis);
	}
}
