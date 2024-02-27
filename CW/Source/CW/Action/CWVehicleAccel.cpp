// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Action/CWVehicleAccel.h"
#include "ChaosVehicleMovementComponent.h"

void UCWVehicleAccel::ExecAction(const FInputActionValue& InputActionValue){
	
	Super::ExecAction(InputActionValue);
	
	ACWWheeledVehiclePawn* Pawn = GetOwner<ACWWheeledVehiclePawn>();
	
	if(Pawn != nullptr){
		
		float tmp = InputActionValue.GetMagnitude();
		
		Pawn->SetThrottle(tmp);
	}
}
