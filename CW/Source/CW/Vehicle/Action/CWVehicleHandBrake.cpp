// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Vehicle/Action/CWVehicleHandBrake.h"
#include "CW/Vehicle/CWWheeledVehiclePawn.h"

void UCWVehicleHandBrake::ExecAction(const FInputActionValue& InputActionValue){
	
	Super::ExecAction(InputActionValue);
	
	ACWWheeledVehiclePawn* Pawn = GetOwner<ACWWheeledVehiclePawn>();
	
	if(Pawn != nullptr){
		
		bool brake = InputActionValue.Get<bool>();
		
		Pawn->SetHandBrake(brake);
	}
}
