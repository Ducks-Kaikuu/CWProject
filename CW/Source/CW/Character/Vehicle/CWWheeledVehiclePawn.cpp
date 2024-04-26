﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "CW/Character/Vehicle/CWWheeledVehiclePawn.h"
#include "CW/CWDef.h"
#include "CW/System/CWGameInstance.h"
#include "CW/Weapon/CWWeaponActorBase.h"

#include "ChaosVehicleMovementComponent.h"
#include "Net/UnrealNetwork.h"
#include "Utility/SNUtility.h"

ACWWheeledVehiclePawn::ACWWheeledVehiclePawn(const FObjectInitializer& Initializer)
	:Super(Initializer)
{
	
}

void ACWWheeledVehiclePawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

//	DOREPLIFETIME(ACWWheeledVehiclePawn, Throttle);
//	DOREPLIFETIME(ACWWheeledVehiclePawn, YAxis);
//	DOREPLIFETIME(ACWWheeledVehiclePawn, XAxis);
//	DOREPLIFETIME(ACWWheeledVehiclePawn, HandBrake);
}

void ACWWheeledVehiclePawn::NotifyRestarted()
{
	Super::NotifyRestarted();

	if(Controller != nullptr)
	{
		if(Controller->IsLocalController() == false)
		{
			if(GetLocalRole() == ROLE_Authority)
			{
				UChaosVehicleMovementComponent* VehicleComponent = GetVehicleMovement();

				if(VehicleComponent != nullptr)
				{
					VehicleComponent->SetRequiresControllerForInputs(false);
					
					CW_LOG(TEXT("SetRequiresControllerForInputs is false."))
				} else
				{
					CW_LOG(TEXT("Vehicle Component is nullptr."))
				}
			}
		} else
		{
			if(GetLocalRole() == ROLE_Authority)
			{
				UChaosVehicleMovementComponent* VehicleComponent = GetVehicleMovement();

				if(VehicleComponent != nullptr)
				{
					VehicleComponent->SetRequiresControllerForInputs(true);

					CW_LOG(TEXT("SetRequiresControllerForInputs is true."))
				} else
				{
					CW_LOG(TEXT("Vehicle Component is nullptr."))
				}
			} else
			{
				SetActorTickEnabled(false);

				UChaosVehicleMovementComponent* VehicleComponent = GetVehicleMovement();

				if(VehicleComponent != nullptr)
				{
					VehicleComponent->SetComponentTickEnabled(false);
				}

				CW_LOG(TEXT("Stopped Vehicle Tick."))
			}
		}
	} else
	{
		if(GetLocalRole() == ROLE_Authority)
		{
			if(GetLocalRole() == ROLE_Authority)
			{
				UChaosVehicleMovementComponent* VehicleComponent = GetVehicleMovement();

				if(VehicleComponent != nullptr)
				{
					VehicleComponent->SetRequiresControllerForInputs(true);

					CW_LOG(TEXT("[Controller None] : SetRequiresControllerForInputs is true."))
				} else
				{
					CW_LOG(TEXT("[Controller None] : Vehicle Component is nullptr."))
				}
			}
		} else
		{
			SetActorTickEnabled(false);

			UChaosVehicleMovementComponent* VehicleComponent = GetVehicleMovement();

			if(VehicleComponent != nullptr)
			{
				VehicleComponent->SetComponentTickEnabled(false);
			}

			CW_LOG(TEXT("Stopped Vehicle Tick."))
		}
	}
}


void	ACWWheeledVehiclePawn::Tick(float DeltaTime){

	Super::Tick(DeltaTime);
	
	UChaosVehicleMovementComponent* VehicleComponent = GetVehicleMovement();
	
	if(VehicleComponent != nullptr)
	{
		
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

	//	ReplicateTransform();
#if 1
		if((Controller == nullptr) || (Controller->IsLocalController() == false)){
			
			FString str00(TEXT("Throttle  Input : ") + FString::SanitizeFloat(VehicleComponent->GetThrottleInput()));
			FString str01(TEXT("Brake     Input : ") + FString::SanitizeFloat(VehicleComponent->GetBrakeInput()));
			FString str02(TEXT("Steering  Input : ") + FString::SanitizeFloat(VehicleComponent->GetSteeringInput()));
			FString str03(TEXT("HandBrake Input : "));
				
			str03 += (VehicleComponent->GetHandbrakeInput() == true ? TEXT("True") : TEXT("False"));
				
			CW_DEBUG_DISPLAY(str00, FLinearColor::Red, 30, 20, 0.0f, 1.0f);
			CW_DEBUG_DISPLAY(str01, FLinearColor::Red, 30, 40, 0.0f, 1.0f);
			CW_DEBUG_DISPLAY(str02, FLinearColor::Red, 30, 60, 0.0f, 1.0f);
			CW_DEBUG_DISPLAY(str03, FLinearColor::Red, 30, 80, 0.0f, 1.0f);
		} else
		{
			FString str00(TEXT("Throttle  Input : ") + FString::SanitizeFloat(VehicleComponent->GetThrottleInput()));
			FString str01(TEXT("Brake     Input : ") + FString::SanitizeFloat(VehicleComponent->GetBrakeInput()));
			FString str02(TEXT("Steering  Input : ") + FString::SanitizeFloat(VehicleComponent->GetSteeringInput()));
			FString str03(TEXT("HandBrake Input : "));
				
			str03 += (VehicleComponent->GetHandbrakeInput() == true ? TEXT("True") : TEXT("False"));
				
			CW_DEBUG_DISPLAY(str00, FLinearColor::Red, 30, 120, 0.0f, 1.0f);
			CW_DEBUG_DISPLAY(str01, FLinearColor::Red, 30, 140, 0.0f, 1.0f);
			CW_DEBUG_DISPLAY(str02, FLinearColor::Red, 30, 160, 0.0f, 1.0f);
			CW_DEBUG_DISPLAY(str03, FLinearColor::Red, 30, 180, 0.0f, 1.0f);
		}
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

void ACWWheeledVehiclePawn::BeginPlay(){
	
	Super::BeginPlay();
	// 武器をロード
	LStreamHandle = GetCWGameInstance()->GetWeaponManager()->LoadWeaponClass(FName(TEXT("AKM")), this, &ACWWheeledVehiclePawn::FinishLoadWeaponL);
	RStreamHandle = GetCWGameInstance()->GetWeaponManager()->LoadWeaponClass(FName(TEXT("RPG")), this, &ACWWheeledVehiclePawn::FinishLoadWeaponR);

	if(InputComponent != nullptr)
	{
		CW_LOG(TEXT("Have Input Component"))
	} else
	{
		CW_LOG(TEXT("None Input Component"))
	}

	CW_LOG(TEXT("BeginPlay"));
}

void ACWWheeledVehiclePawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	CW_LOG(TEXT("PossessedBy"));
}

void ACWWheeledVehiclePawn::UnPossessed()
{
	Super::UnPossessed();

	CW_LOG(TEXT("UnPossessed"));
}

void ACWWheeledVehiclePawn::OnRep_Controller()
{
	Super::OnRep_Controller();

	CW_LOG(TEXT("OnRep_Controller"));
}

void ACWWheeledVehiclePawn::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	CW_LOG(TEXT("OnRep_PlayerState"));
}





void ACWWheeledVehiclePawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for(auto& Weapon:WeaponMap)
	{
		Weapon.Value->ConditionalBeginDestroy();
	}

	WeaponMap.Empty();
	
	CW_LOG(TEXT("EndPlay"));
}


//----------------------------------------------------------------------//
//
//! @brief 左用武器がロードされた場合の処理
//
//----------------------------------------------------------------------//
void ACWWheeledVehiclePawn::FinishLoadWeaponL(){

	ACWWeaponActorBase* Weapon(PostLoadWeapon(LStreamHandle, WeaponLAttachSocket));

	WeaponMap.Add(FName(TEXT("Left")), Weapon);
}

//----------------------------------------------------------------------//
//
//! @brief 右用武器がロードされた場合の処理
//
//----------------------------------------------------------------------//
void ACWWheeledVehiclePawn::FinishLoadWeaponR(){
	
	ACWWeaponActorBase* Weapon(PostLoadWeapon(RStreamHandle, WeaponRAttachSocket));

	WeaponMap.Add(FName("Right"), Weapon);
}

//----------------------------------------------------------------------//
//
//! @brief 武器のロードが終了した後の処理
//
//! @param StreamHandle 非同期ロードに使用したハンドル
//
//----------------------------------------------------------------------//
ACWWeaponActorBase* ACWWheeledVehiclePawn::PostLoadWeapon(TSharedPtr<FStreamableHandle> StreamHandle, FName SocketName){
	// ロードが正常に終了しているかチェック
	if((StreamHandle == nullptr) || (StreamHandle->HasLoadCompleted() == false)){
		return nullptr;
	}
	// ロードしたオブジェクトを取得
	UClass* WeaponClass = Cast<UClass>(StreamHandle->GetLoadedAsset());

	ACWWeaponActorBase* WeaponActor(nullptr);
	// nullチェック
	if(WeaponClass != nullptr)
	{
		FActorSpawnParameters Parameter;
		// オーナーを設定
		Parameter.Owner = this;
		// 武器アクターを生成
		WeaponActor = GetWorld()->SpawnActor<ACWWeaponActorBase>(WeaponClass, Parameter);
		// nullチェック
		if(WeaponActor == nullptr){
			CW_LOG(TEXT("Failed to Spawn Weapon Actor : %s"), *StreamHandle->GetDebugName());
		} else {
			// 武器をアタッチ
			WeaponActor->AttachToOwner(SocketName);
		}
	}

	return WeaponActor;
}

ACWWeaponActorBase* ACWWheeledVehiclePawn::GetWeapon(const FName& Name)
{
	if(WeaponMap.Contains(Name) == false)
	{
		return nullptr;
	}

	return WeaponMap[Name];
}

void ACWWheeledVehiclePawn::ReplicateTransform()
{
	const FTransform& Transform(GetActorTransform());
	
	const FRotator Rotator(Transform.GetRotation().Rotator());

	FVector_NetQuantize10 Rotate(Rotator.Pitch, Rotator.Yaw, Rotator.Roll);
	
	Replicate_OnServer(Transform.GetLocation(), Rotate, true);
}

void ACWWheeledVehiclePawn::Replicate_OnServer_Implementation(const FVector_NetQuantize10& Location, const FVector_NetQuantize10& Rotation, uint8 bSweep)
{
	SetActorLocationAndRotation(Location, FRotator(Rotation.X, Rotation.Y, Rotation.Z), (bool)bSweep, nullptr, ETeleportType::ResetPhysics);
	
	CW_LOG(TEXT("Replicate OnServer."));
}

