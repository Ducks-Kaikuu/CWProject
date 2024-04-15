// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "Character/Base/SNWheeledVehiclePlayerBase.h"
#include "Engine/StreamableManager.h"
#include "CWWheeledVehiclePawn.generated.h"

class USNPawnExtensionComponent;
class ACWWeaponActorBase;
/**
 * 
 */
UCLASS()
class CW_API ACWWheeledVehiclePawn : public ASNWheeledVehiclePlayerBase
{
	GENERATED_BODY()
	
public:

	ACWWheeledVehiclePawn(const FObjectInitializer& Initializer);
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void	Tick(float DeltaTime) override ;
	
	void	SetThrottle(float Value);
	
	void	SetSteer(float X, float Y);
	
	void	SetHandBrake(bool bBrake);

	ACWWeaponActorBase* GetWeapon(const FName& Name);
	
protected:

	void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void UnPossessed() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual void OnRep_Controller() override;

	virtual void OnRep_PlayerState() override;
	
private:
	
	//! @{@name 左用武器がロードされた場合の処理
	void FinishLoadWeaponL();
	//! @}
	
	//! @{@name 右用武器がロードされた場合の処理
	void FinishLoadWeaponR();
	//! @}
	
	//! @{@name 武器のロードが終了した後の処理
	ACWWeaponActorBase* PostLoadWeapon(TSharedPtr<FStreamableHandle> StreamHandle, FName SocketName);
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

	UPROPERTY()
	TMap<FName, TObjectPtr<ACWWeaponActorBase>> WeaponMap;
	
	//!< 武器の非同期ロード用のハンドル
	TSharedPtr<FStreamableHandle> LStreamHandle = nullptr;
	TSharedPtr<FStreamableHandle> RStreamHandle = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lyra|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USNPawnExtensionComponent> PawnExtComponent;
};
