// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWSceneBase.generated.h"

//----------------------------------------------------------------------//
//----------------------------------------------------------------------//
class UCWMasterWidget;

//----------------------------------------------------------------------//
//
//! @brief シーン管理用のベースクラス
//
//----------------------------------------------------------------------//
UCLASS()
class CW_API ACWSceneBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACWSceneBase();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	//! @{@name マスターウィジェットを取得
	UCWMasterWidget* GetMasterWidget();
	//! @}
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	//!< マスターウィジェットクラス情報
	UPROPERTY(EditAnywhere, Category="UserInterface")
	TSoftClassPtr<UCWMasterWidget> MasterWidgetClass = nullptr;
	
	//!< マスターウィジェット
	UPROPERTY()
	TObjectPtr<UCWMasterWidget> MasterWidget = nullptr;
};

//----------------------------------------------------------------------//
//
//! @brief マスターウィジェットを取得
//
//! @retval マスターウィジェット
//
//----------------------------------------------------------------------//
FORCEINLINE UCWMasterWidget* ACWSceneBase::GetMasterWidget(){
	return MasterWidget;
}

