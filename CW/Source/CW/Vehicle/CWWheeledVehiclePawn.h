// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "CWWheeledVehiclePawn.generated.h"

/**
 * 
 */
UCLASS()
class CW_API ACWWheeledVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()
	
public:
	
	void	Tick(float DeltaTime) override ;
	
	void	SetThrottle(float Value);
	
	void	SetSteer(float X, float Y);
	
	void	SetHandBrake(bool bBrake);
	
private:
	
	float Throttle=0.0f;
	
	float YAxis=0.0f;
	
	float XAxis=0.0f;
	
	bool HandBrake=false;
};
