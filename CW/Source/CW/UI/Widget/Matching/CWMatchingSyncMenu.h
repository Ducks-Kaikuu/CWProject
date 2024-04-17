// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/UI/Widget/CWUserWidgetBase.h"
#include "CWMatchingSyncMenu.generated.h"

class UTextBlock;
class UCWButton;

DECLARE_DYNAMIC_DELEGATE(FOnStartButtonClicked);

/**
 * 
 */
UCLASS()
class CW_API UCWMatchingSyncMenu : public UCWUserWidgetBase
{
	GENERATED_BODY()

public:

	bool Initialize() override;

	void SetSessionName(const FName& Name);

	UCWButton* GetStartButton() const;

private:

	
	UPROPERTY()
	TObjectPtr<UTextBlock> SessionName = nullptr;

	UPROPERTY()
	TObjectPtr<UCWButton>	StartButton = nullptr;
};

FORCEINLINE UCWButton* UCWMatchingSyncMenu::GetStartButton() const
{
	return StartButton;
}

