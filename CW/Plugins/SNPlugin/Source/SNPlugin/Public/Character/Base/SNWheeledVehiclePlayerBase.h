// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Base/SNWheeledVehiclePawnBase.h"
#include "SNWheeledVehiclePlayerBase.generated.h"

/**
 * 
 */
UCLASS()
class SNPLUGIN_API ASNWheeledVehiclePlayerBase : public ASNWheeledVehiclePawnBase
{
	GENERATED_BODY()

protected:
	
	//! @{@name プレイヤーインプットコンポーネントの初期化
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	//! @}
};
