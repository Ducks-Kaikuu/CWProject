// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/UI/Widget/CWButton.h"
#include "CW/UI/Widget/CWUserWidgetBase.h"
#include "CWMatchingMenu.generated.h"

class UCWButton;
/**
 * 
 */
UCLASS()
class CW_API UCWMatchingMenu : public UCWUserWidgetBase
{
	GENERATED_BODY()

public:

	bool Initialize() override;

	void BeginDestroy() override;

	UCWButton* GetHostSessionButton();

	UCWButton* GetJoinSessionButton();
	
private:
	UPROPERTY()
	TObjectPtr<UCWButton> HostSessionButton=nullptr;

	UPROPERTY()
	TObjectPtr<UCWButton> JoinSessionButton=nullptr;
};

FORCEINLINE UCWButton* UCWMatchingMenu::GetHostSessionButton()
{
	return HostSessionButton;
}

FORCEINLINE UCWButton* UCWMatchingMenu::GetJoinSessionButton()
{
	return JoinSessionButton;
}

