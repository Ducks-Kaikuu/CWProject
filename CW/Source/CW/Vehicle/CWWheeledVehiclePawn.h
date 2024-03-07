// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Engine/StreamableManager.h"
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

protected:

	void BeginPlay() override;
	
private:
	
	//! @{@name 左用武器がロードされた場合の処理
	void FinishLoadWeaponL();
	//! @}
	
	//! @{@name 右用武器がロードされた場合の処理
	void FinishLoadWeaponR();
	//! @}
	
	//! @{@name 武器のロードが終了した後の処理
	void PostLoadWeapon(TSharedPtr<FStreamableHandle> StreamHandle, FName SocketName);
	//! @}
	
	float Throttle=0.0f;
	
	float YAxis=0.0f;
	
	float XAxis=0.0f;
	
	bool HandBrake=false;
	
	//!< 左側の武器をアタッチするソケット名
	UPROPERTY(EditAnywhere, Category="Vehicle|Weapon")
	FName WeaponLAttachSocket=FName(TEXT("WeaponL"));
	
	//!< 右側の武器をアタッチするソケット名
	UPROPERTY(EditAnywhere, Category="Vehicle|Weapon")
	FName WeaponRAttachSocket=FName(TEXT("WeaponR"));
	
	//!< 武器の非同期ロード用のハンドル
	TSharedPtr<FStreamableHandle> LStreamHandle = nullptr;
	TSharedPtr<FStreamableHandle> RStreamHandle = nullptr;
};
