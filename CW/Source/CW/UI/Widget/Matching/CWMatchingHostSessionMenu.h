// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CW/UI/Widget/CWUserWidgetBase.h"
#include "CWMatchingHostSessionMenu.generated.h"

class UCWButton;
class UComboBoxString;
class UEditableTextBox;
/**
 * 
 */
UCLASS()
class CW_API UCWMatchingHostSessionMenu : public UCWUserWidgetBase
{
	GENERATED_BODY()

public:

	bool Initialize() override;

	FName GetSessionName() const ;

	int GetConnectionNum() const ;

	UCWButton* GetCreateButton() const;

	UCWButton* GetCancelButton() const;
	
private:
	UPROPERTY()
	TObjectPtr<UEditableTextBox> SessionName = nullptr;

	UPROPERTY()
	TObjectPtr<UComboBoxString> ConnectionNum = nullptr;

	UPROPERTY()
	TObjectPtr<UCWButton>		CreateButton = nullptr;

	UPROPERTY()
	TObjectPtr<UCWButton>		CancelButton = nullptr;
};

FORCEINLINE UCWButton* UCWMatchingHostSessionMenu::GetCreateButton() const
{
	return CreateButton;
}

FORCEINLINE UCWButton* UCWMatchingHostSessionMenu::GetCancelButton() const
{
	return CancelButton;
}
