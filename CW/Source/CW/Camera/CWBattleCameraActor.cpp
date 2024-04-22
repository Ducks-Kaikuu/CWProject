// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Camera/CWBattleCameraActor.h"

#include "CWPlayerCameraManager.h"
#include "CW/CWDef.h"
#include "CW/Character/Vehicle/CWWheeledVehiclePawn.h"
#include "Utility/SNUtility.h"

void ACWBattleCameraActor::Tick(float DeltaSeconds){
	
	Super::Tick(DeltaSeconds);

	ACWWheeledVehiclePawn* Player(GetCurrentPlayer());
	
	if(Player != nullptr){
		
		if(bCarFocusedCamera == true){
			// アクターと向きが違うので180度回転
			const FRotator ReverseRotation(0, 180, 0);
			// ターゲットからのオフセットを回転
			FVector Offset(ReverseRotation.RotateVector(TargetOffset));
			// カメラのローテーションを反映
			FVector CameraPosition(CameraRotate.RotateVector(Offset));
			// アタッチするトランスフォームの情報を取得
			FTransform Transform(BoneName != NAME_None ? Player->GetMesh()->GetBoneTransform(BoneName) : Player->GetActorTransform());
			// フォーカス時の高さを加算
			Transform.AddToTranslation(FVector(0.0f, 0.0f, FocuedCameraHeight));
			// 親トランスフォームを反映
			CameraPosition = Transform.TransformPosition(CameraPosition);
			// ターゲットへのベクトルを算出
			FVector Vector(Transform.GetLocation() - CameraPosition);
			// ベクトルをノーマライズ
			bool bSucceed = Vector.Normalize();
			
			if(bSucceed == true){
				// カメラのトランスフォームを生成
				FTransform CameraTransform(Vector.Rotation(), CameraPosition);
				// トランスフォームを設定
				SetActorTransform(CameraTransform);
			} else {
				
				FTransform CameraTransform(FQuat::Identity, CameraPosition);
				
				SetActorTransform(CameraTransform);
			}
			
		} else {
			
			const FRotator ReverseRotation(0, 180, 0);
			
			FVector Offset(ReverseRotation.RotateVector(TargetOffset));
			
			FTransform Transform(BoneName != NAME_None ? Player->GetMesh()->GetBoneTransform(BoneName) : Player->GetActorTransform());
			
			FTransform CameraTransform(CameraRotate, Offset);
			
			CameraTransform = CameraTransform * Transform;
			
			SetActorTransform(CameraTransform);
		}
	}
}
