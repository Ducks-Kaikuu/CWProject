// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/Scene/StateTree/CWMatchingSceneBase.h"
#include "CWMatchingHostSessionTask.generated.h"

class UCWButton;
/**
 * 
 */
UCLASS()
class CW_API UCWMatchingHostSessionTask : public UCWMatchingSceneBase
{
	GENERATED_BODY()

public:
	
	//! @{@name 毎フレームの更新処理
	virtual EStateTreeRunStatus Tick(FStateTreeExecutionContext& Context, const float DeltaTime) override;
	//! @}
	
	//! @{@name タスクの開始処理
	virtual EStateTreeRunStatus EnterState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	//! @}
	
	//! @{@name タスクの終了処理
	virtual void ExitState(FStateTreeExecutionContext& Context, const FStateTreeTransitionResult& Transition) override;
	//! @}

	virtual void HudPostLoad() override;
	
private:
	UFUNCTION()
	void OnCreateButtonClicked(UCWButton* Button);

	UFUNCTION()
	void OnCancelButtonClicked(UCWButton* Button);

	UFUNCTION()
	void OnCompleteHostSession(FName SessionName, bool bWasSuccessful);

	UPROPERTY(EditAnywhere, Category="Lobby")
	TSoftObjectPtr<UObject> LobbyMap;
	
	UPROPERTY(VisibleAnywhere)
	bool bSucceed = false;
	
	bool bCancel = false;
};
