// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Scene/CWSceneBase.h"
#include "CWBattleScene.generated.h"

struct FStreamableHandle;
class UCWUserWidgetBase;
/**
 * 
 */
UCLASS()
class CW_API ACWBattleScene : public ACWSceneBase
{
	GENERATED_BODY()

public:

	ACWBattleScene();
	
protected:
	
	void BeginPlay() override;
	
private:

	void FinishuHudLoad();
	
	UPROPERTY(EditAnywhere, Category="HUD")
	TSoftClassPtr<UCWUserWidgetBase> BattleHudClass = nullptr;;

	UPROPERTY()
	TObjectPtr<UCWUserWidgetBase> BattleHud = nullptr;

	TSharedPtr<FStreamableHandle> HudStreamHandle;
};
