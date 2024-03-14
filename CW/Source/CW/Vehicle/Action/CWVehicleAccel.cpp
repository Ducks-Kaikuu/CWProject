// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Vehicle/Action/CWVehicleAccel.h"
#include "CW/Vehicle/CWWheeledVehiclePawn.h"

void UCWVehicleAccel::ExecAction(const FInputActionValue& InputActionValue){
	
	Super::ExecAction(InputActionValue);
	
	ACWWheeledVehiclePawn* Pawn = GetOwner<ACWWheeledVehiclePawn>();
	
	if(Pawn != nullptr){
		
		float tmp = InputActionValue.GetMagnitude();
		
		Pawn->SetThrottle(tmp);
	}
}
