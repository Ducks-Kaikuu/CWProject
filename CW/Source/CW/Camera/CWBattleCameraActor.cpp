// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Camera/CWBattleCameraActor.h"

#include "SkeletalMeshAttributes.h"
#include "CW/CWDef.h"
#include "CW/Vehicle/CWWheeledVehiclePawn.h"

void ACWBattleCameraActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ACWWheeledVehiclePawn* Player(GetCurrentPlayer());

	if(Player != nullptr)
	{
		const FRotator ReverseRotation(0, 180, 0);

		FVector Offset(ReverseRotation.RotateVector(TargetOffset));
		
		FTransform Transform(BoneName != NAME_None ? Player->GetMesh()->GetBoneTransform(BoneName) : Player->GetActorTransform());
		
		FTransform CameraTransform(CameraRotate, Offset);

		CameraTransform = CameraTransform * Transform;
		
		SetActorTransform(CameraTransform);
	}
	
}
