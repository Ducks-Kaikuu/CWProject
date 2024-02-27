// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Vehicle/CWWheeledVehiclePawn.h"

void	ACWWheeledVehiclePawn::Tick(float DeltaTime){
	
	Super::Tick(DeltaTime);
	
	UChaosVehicleMovementComponent* VehicleComponent = GetVehicleMovement();
	
	if(VehicleComponent != nullptr){
		
		float Value = Throttle;
		
		if(HandBrake == true){
			VehicleComponent->SetBrakeInput   (0.0f);
			VehicleComponent->SetThrottleInput(0.0f);
		} else {
			
			if(YAxis <-0.2f){
				VehicleComponent->SetBrakeInput(Value);
				VehicleComponent->SetThrottleInput(0.0f);
			} else {
				VehicleComponent->SetBrakeInput(0.0f);
				VehicleComponent->SetThrottleInput(Value);
			}
		}
		
//		VehicleComponent->SetThrottleInput(Value);
		VehicleComponent->SetSteeringInput(XAxis);
		VehicleComponent->SetHandbrakeInput(HandBrake);
#if CW_DEBUG
			
			FString str00(TEXT("Throttle  Input : ") + FString::SanitizeFloat(VehicleComponent->GetThrottleInput()));
			FString str01(TEXT("Brake     Input : ") + FString::SanitizeFloat(VehicleComponent->GetBrakeInput()));
			FString str02(TEXT("Steering  Input : ") + FString::SanitizeFloat(VehicleComponent->GetSteeringInput()));
			FString str03(TEXT("HandBrake Input : "));
			
			str03 += (VehicleComponent->GetHandbrakeInput() == true ? TEXT("True") : TEXT("False"));
			
			CW_DEBUG_DISPLAY(str00, FLinearColor::Red, 30, 20, 0.0f, 1.0f);
			CW_DEBUG_DISPLAY(str01, FLinearColor::Red, 30, 40, 0.0f, 1.0f);
			CW_DEBUG_DISPLAY(str02, FLinearColor::Red, 30, 60, 0.0f, 1.0f);
			CW_DEBUG_DISPLAY(str03, FLinearColor::Red, 30, 80, 0.0f, 1.0f);
#endif
	}
}

void	ACWWheeledVehiclePawn::SetThrottle(float Value){
	Throttle = Value;
}

void	ACWWheeledVehiclePawn::SetSteer(float X, float Y){
	XAxis = X;
	YAxis = Y;
}

void	ACWWheeledVehiclePawn::SetHandBrake(bool bBrake){
	
	HandBrake = bBrake;
	
	if(bBrake == true){
		Throttle = 0.0f;
	}
}
