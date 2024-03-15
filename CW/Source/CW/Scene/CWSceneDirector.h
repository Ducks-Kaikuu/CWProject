// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Scene/CWSceneBase.h"
#include "CWSceneDirector.generated.h"

/**
 * 
 */
UCLASS()
class CW_API ACWSceneDirector : public ACWSceneBase
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleAnywhere)
	bool bTest = false;
};
