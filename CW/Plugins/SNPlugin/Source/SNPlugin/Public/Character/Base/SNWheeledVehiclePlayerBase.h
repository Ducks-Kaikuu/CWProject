// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SNPlayablePawnInterface.h"
#include "Character/Base/SNWheeledVehiclePawnBase.h"
#include "SNWheeledVehiclePlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class SNPLUGIN_API ASNWheeledVehiclePlayerBase : public ASNWheeledVehiclePawnBase, public ISNPlayablePawnInterface
{
	GENERATED_BODY()

public:

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	virtual void AddInputAction(const FName& Name, USNActionBase* Action) override;
	
	virtual USNActionBase* GetAction(const FName& Name) override;

	virtual void ExecuteActionOnServer(const FName& Name, const FInputActionValue& InputActionValue) override;
	
protected:
	
	//! @{@name プレイヤーインプットコンポーネントの初期化
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//! @}

private:
	UFUNCTION(Server, Reliable)
	void ExecuteInputAction_OnServer(const FName& Name, const FInputActionValue& InputActionValue);
	
	UPROPERTY()
	TMap<FName, TObjectPtr<USNActionBase>> InputActionMap;
};
