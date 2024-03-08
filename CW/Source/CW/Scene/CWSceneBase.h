// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CWSceneBase.generated.h"

class UCWMasterWidget;

UCLASS()
class CW_API ACWSceneBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACWSceneBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UCWMasterWidget* GetMasterWidget();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, Category="UserInterface")
	TSoftClassPtr<UCWMasterWidget> MasterWidgetClass = nullptr;

	UPROPERTY()
	TObjectPtr<UCWMasterWidget> MasterWidget = nullptr;
};

FORCEINLINE UCWMasterWidget* ACWSceneBase::GetMasterWidget()
{
	return MasterWidget;
}

